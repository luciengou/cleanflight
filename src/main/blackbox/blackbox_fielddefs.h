/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

typedef enum FlightLogFieldCondition {
    FLIGHT_LOG_FIELD_CONDITION_ALWAYS = 0,
    FLIGHT_LOG_FIELD_CONDITION_AT_LEAST_MOTORS_1,
    FLIGHT_LOG_FIELD_CONDITION_AT_LEAST_MOTORS_2,
    FLIGHT_LOG_FIELD_CONDITION_AT_LEAST_MOTORS_3,
    FLIGHT_LOG_FIELD_CONDITION_AT_LEAST_MOTORS_4,
    FLIGHT_LOG_FIELD_CONDITION_AT_LEAST_MOTORS_5,
    FLIGHT_LOG_FIELD_CONDITION_AT_LEAST_MOTORS_6,
    FLIGHT_LOG_FIELD_CONDITION_AT_LEAST_MOTORS_7,
    FLIGHT_LOG_FIELD_CONDITION_AT_LEAST_MOTORS_8,
    FLIGHT_LOG_FIELD_CONDITION_TRICOPTER,

    FLIGHT_LOG_FIELD_CONDITION_MAG,
    FLIGHT_LOG_FIELD_CONDITION_BARO,
    FLIGHT_LOG_FIELD_CONDITION_VBAT,
    FLIGHT_LOG_FIELD_CONDITION_AMPERAGE_ADC,
    FLIGHT_LOG_FIELD_CONDITION_SONAR,

    FLIGHT_LOG_FIELD_CONDITION_NONZERO_PID_D_0,
    FLIGHT_LOG_FIELD_CONDITION_NONZERO_PID_D_1,
    FLIGHT_LOG_FIELD_CONDITION_NONZERO_PID_D_2,

    FLIGHT_LOG_FIELD_CONDITION_NOT_LOGGING_EVERY_FRAME,

    FLIGHT_LOG_FIELD_CONDITION_NEVER,

    FLIGHT_LOG_FIELD_CONDITION_FIRST = FLIGHT_LOG_FIELD_CONDITION_ALWAYS,
    FLIGHT_LOG_FIELD_CONDITION_LAST = FLIGHT_LOG_FIELD_CONDITION_NEVER
} FlightLogFieldCondition;

typedef enum FlightLogFieldPredictor {
    //No prediction:
    FLIGHT_LOG_FIELD_PREDICTOR_0              = 0,

    //Predict that the field is the same as last frame:
    FLIGHT_LOG_FIELD_PREDICTOR_PREVIOUS       = 1,

    //Predict that the slope between this field and the previous item is the same as that between the past two history items:
    FLIGHT_LOG_FIELD_PREDICTOR_STRAIGHT_LINE  = 2,

    //Predict that this field is the same as the average of the last two history items:
    FLIGHT_LOG_FIELD_PREDICTOR_AVERAGE_2      = 3,

    //Predict that this field is minthrottle
    FLIGHT_LOG_FIELD_PREDICTOR_MINTHROTTLE    = 4,

    //Predict that this field is the same as motor 0
    FLIGHT_LOG_FIELD_PREDICTOR_MOTOR_0        = 5,

    //This field always increments
    FLIGHT_LOG_FIELD_PREDICTOR_INC            = 6,

    //Predict this GPS co-ordinate is the GPS home co-ordinate (or no prediction if that coordinate is not set)
    FLIGHT_LOG_FIELD_PREDICTOR_HOME_COORD     = 7,

    //Predict 1500
    FLIGHT_LOG_FIELD_PREDICTOR_1500           = 8,

    //Predict vbatref, the reference ADC level stored in the header
    FLIGHT_LOG_FIELD_PREDICTOR_VBATREF        = 9,

    //Predict the last time value written in the main stream
    FLIGHT_LOG_FIELD_PREDICTOR_LAST_MAIN_FRAME_TIME = 10

} FlightLogFieldPredictor;

typedef enum FlightLogFieldEncoding {
    FLIGHT_LOG_FIELD_ENCODING_SIGNED_VB       = 0, // Signed variable-byte
    FLIGHT_LOG_FIELD_ENCODING_UNSIGNED_VB     = 1, // Unsigned variable-byte
    FLIGHT_LOG_FIELD_ENCODING_NEG_14BIT       = 3, // Unsigned variable-byte but we negate the value before storing, value is 14 bits
    FLIGHT_LOG_FIELD_ENCODING_TAG8_8SVB       = 6,
    FLIGHT_LOG_FIELD_ENCODING_TAG2_3S32       = 7,
    FLIGHT_LOG_FIELD_ENCODING_TAG8_4S16       = 8,
    FLIGHT_LOG_FIELD_ENCODING_NULL            = 9 // Nothing is written to the file, take value to be zero
} FlightLogFieldEncoding;

typedef enum FlightLogFieldSign {
    FLIGHT_LOG_FIELD_UNSIGNED = 0,
    FLIGHT_LOG_FIELD_SIGNED   = 1
} FlightLogFieldSign;

typedef enum FlightLogEvent {
    FLIGHT_LOG_EVENT_SYNC_BEEP = 0,
    FLIGHT_LOG_EVENT_AUTOTUNE_CYCLE_START = 10,
    FLIGHT_LOG_EVENT_AUTOTUNE_CYCLE_RESULT = 11,
    FLIGHT_LOG_EVENT_AUTOTUNE_TARGETS = 12,
    FLIGHT_LOG_EVENT_LOG_END = 255
} FlightLogEvent;

typedef struct flightLogEvent_syncBeep_t {
    uint32_t time;
} flightLogEvent_syncBeep_t;

typedef struct flightLogEvent_autotuneCycleStart_t {
    uint8_t phase;
    uint8_t cycle;
    uint8_t p;
    uint8_t i;
    uint8_t d;
    uint8_t rising;
} flightLogEvent_autotuneCycleStart_t;

#define FLIGHT_LOG_EVENT_AUTOTUNE_FLAG_OVERSHOT 1
#define FLIGHT_LOG_EVENT_AUTOTUNE_FLAG_TIMEDOUT 2

typedef struct flightLogEvent_autotuneCycleResult_t {
    uint8_t flags;
    uint8_t p;
    uint8_t i;
    uint8_t d;
} flightLogEvent_autotuneCycleResult_t;

typedef struct flightLogEvent_autotuneTargets_t {
    uint16_t currentAngle;
    int8_t targetAngle, targetAngleAtPeak;
    uint16_t firstPeakAngle, secondPeakAngle;
} flightLogEvent_autotuneTargets_t;

typedef union flightLogEventData_t
{
    flightLogEvent_syncBeep_t syncBeep;
    flightLogEvent_autotuneCycleStart_t autotuneCycleStart;
    flightLogEvent_autotuneCycleResult_t autotuneCycleResult;
    flightLogEvent_autotuneTargets_t autotuneTargets;
} flightLogEventData_t;

typedef struct flightLogEvent_t
{
    FlightLogEvent event;
    flightLogEventData_t data;
} flightLogEvent_t;
