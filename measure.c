/* SECU-3  - An open source, free engine control unit
   Copyright (C) 2007 Alexey A. Shabelnikov. Ukraine, Gorlovka

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   contacts:
              http://secu-3.narod.ru
              email: secu-3@yandex.ru
*/

#include <inavr.h>
#include <ioavr.h>
#include "measure.h"
#include "adc.h"
#include "secu3.h"

//��������� ��������� �������� �������
#define GET_GAS_VALVE_STATE(s) (PINC_Bit6)

//��������� ��������� ����������� �������� (������ ��������, ��� ��������)
#define GET_THROTTLE_GATE_STATE(s) (PINC_Bit5)

//���-�� �������� ��� ���������� ������� �������� �.�.
#define FRQ_AVERAGING           16                          
#define FRQ4_AVERAGING          4

//������ ������� ���������� �� ������� ����������� �������
#define MAP_AVERAGING           4   
#define BAT_AVERAGING           4   
#define TMP_AVERAGING           8  

uint16_t freq_circular_buffer[FRQ_AVERAGING];     //����� ���������� ������� �������� ���������
uint16_t freq4_circular_buffer[FRQ4_AVERAGING];   //
uint16_t map_circular_buffer[MAP_AVERAGING];      //����� ���������� ����������� ��������
uint16_t ubat_circular_buffer[BAT_AVERAGING];     //����� ���������� ���������� �������� ����
uint16_t temp_circular_buffer[TMP_AVERAGING];     //����� ���������� ����������� ����������� ��������

//���������� ������� ���������� (������� ��������, �������...)
void meas_update_values_buffers(struct ecudata_t* d)
{
 static uint8_t  map_ai  = MAP_AVERAGING-1;
 static uint8_t  bat_ai  = BAT_AVERAGING-1;
 static uint8_t  tmp_ai  = TMP_AVERAGING-1;      
 static uint8_t  frq_ai  = FRQ_AVERAGING-1;
 static uint8_t  frq4_ai = FRQ4_AVERAGING-1;  

 map_circular_buffer[map_ai] = adc_get_map_value();      
 (map_ai==0) ? (map_ai = MAP_AVERAGING - 1): map_ai--;            

 ubat_circular_buffer[bat_ai] = adc_get_ubat_value();      
 (bat_ai==0) ? (bat_ai = BAT_AVERAGING - 1): bat_ai--;            

 temp_circular_buffer[tmp_ai] = adc_get_temp_value();      
 (tmp_ai==0) ? (tmp_ai = TMP_AVERAGING - 1): tmp_ai--;               

 freq_circular_buffer[frq_ai] = d->sens.inst_frq;      
 (frq_ai==0) ? (frq_ai = FRQ_AVERAGING - 1): frq_ai--; 
        
 freq4_circular_buffer[frq4_ai] = d->sens.inst_frq;      
 (frq4_ai==0) ? (frq4_ai = FRQ4_AVERAGING - 1): frq4_ai--;   
  
 d->sens.knock_k = adc_get_knock_value() * 2;
}

//���������� ���������� ������� ��������� ������� �������� ��������� ������� ����������, ����������� 
//������������ ���, ������� ���������� �������� � ���������� ��������.
void meas_average_measured_values(struct ecudata_t* d)
{     
 uint8_t i;  uint32_t sum;       
            
 for (sum=0,i = 0; i < MAP_AVERAGING; i++)  //��������� �������� � ������� ����������� ��������
  sum+=map_circular_buffer[i];       
 d->sens.map_raw = adc_compensate((sum/MAP_AVERAGING)*2,d->param.map_adc_factor,d->param.map_adc_correction); 
 d->sens.map = map_adc_to_kpa(d->sens.map_raw, d->param.map_curve_offset, d->param.map_curve_gradient);
          
 for (sum=0,i = 0; i < BAT_AVERAGING; i++)   //��������� ���������� �������� ����
  sum+=ubat_circular_buffer[i];      
 d->sens.voltage_raw = adc_compensate((sum/BAT_AVERAGING)*6,d->param.ubat_adc_factor,d->param.ubat_adc_correction);
 d->sens.voltage = ubat_adc_to_v(d->sens.voltage_raw);  
     
 if (d->param.tmp_use) 
 {       
  for (sum=0,i = 0; i < TMP_AVERAGING; i++) //��������� ����������� (����)
   sum+=temp_circular_buffer[i];      
  d->sens.temperat_raw = adc_compensate((5*(sum/TMP_AVERAGING))/3,d->param.temp_adc_factor,d->param.temp_adc_correction); 
  d->sens.temperat = temp_adc_to_c(d->sens.temperat_raw);
 }  
 else                                       //���� �� ������������
  d->sens.temperat = 0;
               
 for (sum=0,i = 0; i < FRQ_AVERAGING; i++)  //��������� ������� �������� ���������
  sum+=freq_circular_buffer[i];      
 d->sens.frequen=(sum/FRQ_AVERAGING);    
  
 for (sum=0,i = 0; i < FRQ4_AVERAGING; i++) //��������� ������� �������� ���������
  sum+=freq4_circular_buffer[i];      
 d->sens.frequen4=(sum/FRQ4_AVERAGING);           
}

//�������� ��� ���������������� ��������� ����� ������ ���������. �������� ������ ����� 
//������������� ���.
void meas_initial_measure(struct ecudata_t* d)
{ 
 uint8_t _t, i = 16;
 _t=__save_interrupt();
 __enable_interrupt();
 do
 {
  adc_begin_measure();                                                     
  while(!adc_is_measure_ready()); 
                      
  meas_update_values_buffers(d);
 }while(--i);            
 __restore_interrupt(_t);
 meas_average_measured_values(d);  
}

void meas_take_discrete_inputs(struct ecudata_t *d)
{
 //--�������� ��������� ����������� ���� ����������, ���������/���������� ������� ����
 d->sens.carb=d->param.carb_invers^GET_THROTTLE_GATE_STATE(); //���������: 0 - �������� ������, 1 - ������

 //��������� � ��������� ��������� �������� �������
 d->sens.gas = GET_GAS_VALVE_STATE();   

 //����������� ��� ������� � ����������� �� ��������� �������� �������
 if (d->sens.gas)
  d->fn_dat = (__flash f_data_t*)&tables[d->param.fn_gas];    //�� ����
 else  
  d->fn_dat = (__flash f_data_t*)&tables[d->param.fn_benzin];//�� �������     
}

