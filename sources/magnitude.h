/* SECU-3  - An open source, free engine control unit
   Copyright (C) 2007 Alexey A. Shabelnikov. Ukraine, Kiev

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
              http://secu-3.org
              email: shabelnikov@secu-3.org
*/

/** \file magnitude.h
 * \author Alexey A. Shabelnikov
 * Helpful macros for working with constants when fixed point representation of fractional numbers is used
 * (��������������� ������� ��� ������ � ������������ ���������� ��� ������������� ��������������
 * ������������� ������� �����).
 */

#ifndef _MAGNITUDE_H_
#define _MAGNITUDE_H_

#include "adc.h"

/**Used for rounding-up when transforming from floating point value into integer.
 * Note: it is intended for use with constants
 * (��������� ��� ���������� ��� �������������� �� ����� � ��������� ������
 * � ����� �����).
 */
#define ROUND(x) ((int16_t)( (x) + 0.5 - ((x) < 0) ))
/**32 bit integer version of ROUND() */
#define ROUND32(x) ((int32_t)( (x) + 0.5 - ((x) < 0) ))


/**������������ ���������� �������� - ��� */
#define MAP_PHYSICAL_MAGNITUDE_MULTIPLIER  64

/**������������ ���������� �������� - ���������� */
#define UBAT_PHYSICAL_MAGNITUDE_MULTIPLIER (1.0/ADC_DISCRETE) //=400

/**������������ ���������� �������� - ���� */
#define TEMP_PHYSICAL_MAGNITUDE_MULTIPLIER (TSENS_SLOPP / ADC_DISCRETE) //=4

/**������������ ������������� % �������� ����������� �������� (����)*/
#define TPS_PHYSICAL_MAGNITUDE_MULTIPLIER 2

/**Gas dose stepper motor discretes per 1 step */
#define GD_PHYSICAL_MAGNITUDE_MULTIPLIER 2

/* Following macros are necessary when transforming floating point constant-values into integers.
 * Values of phisical magnitudes stored in integers
 * (������ ������� ���������� ��� �������������� ������-�������� � ��������� �������
 * � ����� �����. �������� ���������� ������� �������� � ����� ������).
 */

/** Transforms floating point value of advance angle to fixed point value */
#define ANGLE_MAGNITUDE(a) ROUND ((a) * ANGLE_MULTIPLIER)

/** Transforms floating point value of temperature to fixed point value */
#define TEMPERATURE_MAGNITUDE(t) ROUND ((t) * TEMP_PHYSICAL_MAGNITUDE_MULTIPLIER)

/** Transforms floating point value of voltage to fixed point value */
#define VOLTAGE_MAGNITUDE(t) ROUND ((t) * UBAT_PHYSICAL_MAGNITUDE_MULTIPLIER)

/** Transforms floating point value of pressure(MAP) to fixed point value */
#define PRESSURE_MAGNITUDE(t) ROUND ((t) * MAP_PHYSICAL_MAGNITUDE_MULTIPLIER)

/** Transforms floating point value of percentage of opening (TPS) to fixed point value */
#define TPS_MAGNITUDE(t) ROUND ((t) * TPS_PHYSICAL_MAGNITUDE_MULTIPLIER)

/** Transforms floating point value of percentage of gas dose position to fixed point value */
#define GD_MAGNITUDE(t) ROUND ((t) * GD_PHYSICAL_MAGNITUDE_MULTIPLIER)

/** Transforms ADC compensation factor to fixed point value */
#define ADC_COMP_FACTOR(f) ROUND((f) * 16384)
/** Transforms ADC compensation correction to fixed point value */
#define ADC_COMP_CORR(f, c) ROUND32(16384 * (0.5 - ((-(c)) / ADC_DISCRETE) * (f)))

#endif //_MAGNITUDE_H_
