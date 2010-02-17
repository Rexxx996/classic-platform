/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/








#ifndef DEM_LCFG_H_
#define DEM_LCFG_H_

#include "Dem_Types.h"
#include "Dcm_Types.h"


/*
 * Callback function prototypes
 */

// InitMonitorForEvent
typedef Std_ReturnType (*Dem_CallbackInitMonitorForEventFncType)(Dem_InitMonitorKindType InitMonitorKind);

// InitMonitorForFunction
typedef Std_ReturnType (*Dem_CallbackInitMonitorForFunctionFncType)(void);

// EventStatusChanged
typedef Std_ReturnType (*Dem_CallbackEventStatusChangedFncType)(Dem_EventStatusExtendedType EventStatusOld, Dem_EventStatusExtendedType EventStatusNew);

// DTCStatusChanged
typedef Std_ReturnType (*Dem_CallbackDTCStatusChangedFncType)(uint8 DTCStatusOld, uint8 DTCStatusNew);

// DIDServices
typedef Std_ReturnType (*Dem_CallbackConditionCheckReadFncType)(Dcm_NegativeResponseCodeType *Nrc);
typedef Std_ReturnType (*Dem_CallbackReadDataFncType)(uint8 *Data);
typedef Std_ReturnType (*Dem_CallbackReadDataLength)(uint16 *DidLength);

// GetExtendedDataRecord
typedef Std_ReturnType (*Dem_CallbackGetExtDataRecordFncType)(uint8 *ExtendedDataRecord);

// GetFaultDetectionCounter
typedef Std_ReturnType (*Dem_CallbackGetFaultDetectionCounterFncType)(sint8 *EventIdFaultDetectionCounter);

// GetPIDValue
typedef Std_ReturnType (*Dem_CallbackGetPIDValueFncType)(uint8 *DataValueBuffer);

/*
 * DemGeneral types
 */

// 10.2.25 DemEnableCondition
typedef struct {
	boolean EnableConditionStatus;		//
	// uint16	EnableConditionID;		// Optional
} Dem_EnableConditionType;

// 10.2.30 DemExtendedDataRecordClass
typedef struct {
	uint16	RecordNumber;						// (1)
	uint16	DataSize;							// (1)
	Dem_CallbackGetExtDataRecordFncType	CallbackGetExtDataRecord;// (1)
} Dem_ExtendedDataRecordClassType;

// 10.2.13 DemExtendedDataClass
typedef struct {
	const Dem_ExtendedDataRecordClassType *const ExtendedDataRecordClassRef[DEM_MAX_NR_OF_RECORDS_IN_EXTENDED_DATA+1]; // (1..253)
} Dem_ExtendedDataClassType;

// 10.2.8 DemPidOrDid
typedef struct {
	boolean									PidOrDidUsePort;			// (1)
	uint8									PidOrDidSize;				// (1)
	uint16									DidIdentifier;				// (0..1)
	Dem_CallbackConditionCheckReadFncType	DidConditionCheckReadFnc;	// (0..1)
	Dem_CallbackReadDataLength				DidReadDataLengthFnc;		// (0..1)
	Dem_CallbackReadDataFncType				DidReadFnc;					// (0..1)
	uint8									PidIndentifier;				// (0..1)
	Dem_CallbackGetPIDValueFncType			PidReadFnc;					// (0..1)
} Dem_PidOrDidType;

// 10.2.18 DemFreezeFrameClass
typedef struct {
	Dem_FreezeFrameKindType FFKind;			// (1)
//	uint8					FFRecordNumber;	// (1) Optional
//	const Dem_PidOrDidType 	*FFIdClassRef; 	// (1..255) Optional?
} Dem_FreezeFrameClassType;

// 10.2.4 DemIndicator
typedef struct {
	uint16	Indicator;		// (1)
} Dem_IndicatorType;

// 10.2.28 DemNvramBlockId
typedef struct {
	// TODO: Fill out
} Dem_NvramBlockIdType;

/*
 * DemConfigSetType types
 */

// 10.2.6 DemCallbackDTCStatusChanged
typedef struct {
	Dem_CallbackDTCStatusChangedFncType CallbackDTCStatusChangedFnc;	// (0..1)
} Dem_CallbackDTCStatusChangedType;

// 10.2.26 DemCallbackInitMForF
typedef struct {
	Dem_CallbackInitMonitorForFunctionFncType	CallbackInitMForF;		// (0..1)
} Dem_CallbackInitMForFType;

// 10.2.17 DemDTCClass
typedef struct {
	uint32									DTC;						// (1)
	uint8									DTCFunctionalUnit;			// (1)
	Dem_DTCKindType							DTCKind;					// (1)
	const Dem_CallbackDTCStatusChangedType	*CallbackDTCStatusChanged;	// (0..*)
	const Dem_CallbackInitMForFType			*CallbackInitMForF;			// (0..*)
	// Dem_DTCSeverityType					DTCSeverity					// (0..1)  Optional
	boolean									Arc_EOL;
} Dem_DTCClassType;

// 10.2.5 DemCallbackEventStatusChanged
typedef struct {
	Dem_CallbackEventStatusChangedFncType	CallbackEventStatusChangedFnc;	// (0..1)
} Dem_CallbackEventStatusChangedType;

// 10.2.27 DemCallbackInitMForE
typedef struct {
	Dem_CallbackInitMonitorForEventFncType	CallbackInitMForEFnc;	// (0..1)
} Dem_CallbackInitMforEType;

typedef struct {
	Dem_IndicatorStatusType	IndicatorBehaviour;			// (1)
	Dem_IndicatorType		*LinkedIndicator;			// (1)
} Dem_IndicatorAttributeType;

typedef struct {
	Dem_CallbackGetFaultDetectionCounterFncType	CallbackGetFDCnt;	// (1)
} Dem_PreDebounceMonitorInternalType;

typedef struct {
	// TODO: Fill out
} Dem_PreDebounceCounterBasedType;

typedef struct {
	// TODO: Fill out
} Dem_PreDebounceFrequencyBasedType;

typedef struct {
	// TODO: Fill out
} Dem_PreDebounceTimeBasedType;

typedef struct {
	Dem_PreDebounceNameType		PreDebounceName;						// (1)
	union {
	const Dem_PreDebounceMonitorInternalType	*PreDebounceMonitorInternal;	// (0..1)
	const Dem_PreDebounceCounterBasedType		*PreDebounceCouterBased;		// (0..1)
	const Dem_PreDebounceFrequencyBasedType		*PreDebounceFrequencyBased;		// (0..1)
	const Dem_PreDebounceTimeBasedType			*PreDebounceTimeBased;			// (0..1)
	} PreDebounceAlgorithm;
} Dem_PreDebounceAlgorithmClassType;

// 10.2.14 DemEventClass
typedef struct {
	boolean						ConsiderPtoStatus;									// (1)
	const Dem_DTCOriginType 	EventDestination[DEM_MAX_NR_OF_EVENT_DESTINATION+1];// (0..4)
	uint8						EventPriority;										// (1)
	boolean						FFPrestorageSupported;								// (1)
	boolean						HealingAllowed;										// (1)
	Dem_OperationCycleIdType	OperationCycleRef;									// (1)
//	uint8					HealingCycleCounter;									// (0..1) Optional
//	const Dem_EnableConditionType	*EnableConditionRef;							// (0..*) Optional
//	const Dem_OperationCycleTgtType *HealingCycleRef;								// (0..1) Optional
	const Dem_PreDebounceAlgorithmClassType	*PreDebounceAlgorithmClass;				// (0..255) (Only one supported)
	const Dem_IndicatorAttributeType		*IndicatorAttribute;					// (0..255)
//	Dem_OEMSPecific

} Dem_EventClassType;

// 10.2.12 DemEventParameter
typedef struct {
	uint16										EventID;					// (1)
	Dem_EventKindType							EventKind;					// (1)
	const Dem_EventClassType					*EventClass;				// (1)
	const Dem_ExtendedDataClassType				*ExtendedDataClassRef;		// (0..1)
	const Dem_FreezeFrameClassType				*FreezeFrameClassRef;		// (0..255)
	const Dem_CallbackInitMforEType				*CallbackInitMforE;			// (0..1)
	const Dem_CallbackEventStatusChangedType	*CallbackEventStatusChanged;// (0..*)
	const Dem_DTCClassType						*DTCClassRef;				// (0..1)
	boolean										Arc_EOL;
} Dem_EventParameterType;

// 10.2.19 DemGroupOfDTC
typedef struct {
	// TODO: Fill out
} Dem_GroupOfDtcType;

// 10.2.10 DemOemIdClass
typedef struct {
	uint8	OemID;	// (Pre+Post)
} Dem_OemIdClassType;

// 10.2.9 DemConfigSet
typedef struct {
	const Dem_EventParameterType	*EventParameter;	// (0..65535)
	const Dem_DTCClassType 			*DTCClass;			// (1..16777214)
	const Dem_GroupOfDtcType		*GroupOfDtc;		// (1.16777214)
	const Dem_OemIdClassType		*OemIdClass;		// (0..*)
} Dem_ConfigSetType;

// 10.2.2 Dem
typedef struct {
	const Dem_ConfigSetType *ConfigSet;	//	(1)
} Dem_ConfigType;


/*
 * Make the DEM_Config visible for others.
 */
extern const Dem_ConfigType DEM_Config;


#endif /*DEM_LCFG_H_*/
