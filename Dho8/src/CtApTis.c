/*
 * File: CtApTb.c
 *
 * Code generated for Simulink model 'CtApTb'.
 *
 * Model version                  : 1.122
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jun 26 18:40:27 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Infineon->TriCore
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CtApTis.h"
ENU_OverallEemState EemStates;

/* Model step function */
void CtApTis_step(void)
{
  /* local block i/o variables */
  SG_jTBR2_PropB
    rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_0_BusCrea;
  SG_jVbmsBrc_VbmAlive
    rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_1_BusCrea;
  SG_jVbmcBrc_SystemStatus
    rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_2_BusCrea;
  Bus_CtrlIoResp rtb_TB_RawCore_ref_o16;
  Bus_CtrlIoResp rtb_TB_RawCore_ref_o17;
  uint16_T rtb_SignalConversion9;
  uint16_T rtb_TB_RawCore_ref_o19;
  uint8_T rtb_SignalConversion1_e;
  uint8_T rtb_SignalConversion2_p;
  uint8_T rtb_SignalConversion8_i;
  uint8_T rtb_TB_RawCore_ref_o18;
  uint8_T rtb_TB_RawCore_ref_o20;
  boolean_T rtb_SignalConversion5_i;
  boolean_T rtb_SignalConversion2_n;
  boolean_T rtb_SignalConversion1_h;

  /* SignalConversion: '<Root>/Signal Conversion5' incorporates:
   *  Inport: '<Root>/jTBR2_PropB_ind_b'
   */
  rtb_SignalConversion5_i = getFlag_jTBR2_PropB();

  /* SignalConversion: '<Root>/Signal Conversion2' incorporates:
   *  Inport: '<Root>/jVbmsBrc_VbmAlive_ind_b'
   */
  rtb_SignalConversion2_n = getFlag_jVbmsBrc_VbmAlive();

  /* SignalConversion: '<Root>/Signal Conversion1' incorporates:
   *  Inport: '<Root>/jVbmcBrcSystemStatus_ind_b'
   */
  rtb_SignalConversion1_h = getFlag_jVbmcBrcSystemStatus();

  /* SignalConversion: '<S1>/Signal Conversion1' incorporates:
   *  Inport: '<Root>/internal_TrailBrkPrkEhvState'
   */
  rtb_SignalConversion1_e = getTrailBrkPrkEhvState();

  /* SignalConversion: '<S1>/Signal Conversion2' incorporates:
   *  Inport: '<Root>/internal_TrailBrkSrvEhvState'
   */
  rtb_SignalConversion2_p = getTrailBrkSrvEhvState();

  /* SignalConversion: '<Root>/Signal Conversion8' incorporates:
   *  Inport: '<Root>/TrailBrkHydBlckPar'
   */
  rtb_SignalConversion8_i = getTrailBrkHydBlckPar();

  /* SignalConversion: '<Root>/Signal Conversion9' incorporates:
   *  Inport: '<Root>/TrailBrkHydPreshotPressPar'
   */
  rtb_SignalConversion9 = getTrailBrkHydPreshotPressPar();

  /* Outputs for Atomic SubSystem: '<Root>/RCtApTb' */
  /* BusCreator: '<S3>/BusConversion_InsertedFor_TB_RawCore_ref_at_inport_0' incorporates:
   *  Inport: '<Root>/rx_jTBR2_PropBBrakeLeft_b'
   *  Inport: '<Root>/rx_jTBR2_PropBBrakeRight_b'
   *  Inport: '<Root>/rx_jTBR2_PropBParkLockStatusActVal_b'
   *  Inport: '<Root>/rx_jTBR2_PropBSecondaryBrakePosition_s'
   *  Inport: '<Root>/rx_jTBR2_PropBSecondaryBrakeSwitch_b'
   *  Inport: '<Root>/rx_jTBR2_PropBTBR2_Counter_b'
   *  Inport: '<Root>/rx_jTBR2_PropBTBR2_Crc_b'
   *  Inport: '<Root>/rx_jTBR2_PropBTrailerParkBrakeReleaseRq_b'
   *  Inport: '<Root>/rx_jTBR2_PropBWheelBasedVehicleSpeed_b'
   */
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_0_BusCrea.SecondaryBrakePosition
    = getSecondaryBrakePosition();
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_0_BusCrea.TrailerParkBrakeReleaseRq
    = getTrailerParkBrakeReleaseRq();
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_0_BusCrea.ParkLockStatusActVal
    = getOutBrkParkLock();
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_0_BusCrea.BrakeRight =
    getOutBrkRight();
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_0_BusCrea.BrakeLeft =
    getOutBrkLeft();
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_0_BusCrea.WheelBasedVehicleSpeed
    = getVehSpd();
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_0_BusCrea.SecondaryBrakeSwitch
    = getSecondaryBrakeSwitchActVal();
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_0_BusCrea.TBR2_Counter =
    getTBR2_Counter();
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_0_BusCrea.TBR2_Crc =
    getTBR2_Crc();

  /* BusCreator: '<S3>/BusConversion_InsertedFor_TB_RawCore_ref_at_inport_1' incorporates:
   *  Inport: '<Root>/rx_jVbmsBrc_VbmAliveModuleAliveMsgCounter_b'
   *  Inport: '<Root>/rx_jVbmsBrc_VbmAliveModuleStatus_b'
   */
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_1_BusCrea.ModuleAliveMsgCounter
    = getAlive_Counter();
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_1_BusCrea.ModuleStatus =
    getAlive_Status();

  /* BusCreator: '<S3>/BusConversion_InsertedFor_TB_RawCore_ref_at_inport_2' incorporates:
   *  Inport: '<Root>/rx_jVbmcBrcSDiagInhibit_b'
   *  Inport: '<Root>/rx_jVbmcBrcSOverallEemState_b'
   */
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_2_BusCrea.OverallEemState
    = getOverallEemState();
  rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_2_BusCrea.DiagInhibit =
    getDiagInhibit();

  /* ModelReference: '<S3>/TB_RawCore_ref' */
  TB_RawCore_ref
    (&rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_0_BusCrea,
     &rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_1_BusCrea,
     &rtb_BusConversion_InsertedFor_TB_RawCore_ref_at_inport_2_BusCrea,
     &rtb_SignalConversion5_i, &rtb_SignalConversion2_n,
     &rtb_SignalConversion1_h, &rtb_SignalConversion1_e,
     &rtb_SignalConversion2_p, &rtb_SignalConversion8_i,
     &CtApTb_ConstB.SignalConversion7_n, &CtApTb_ConstB.SignalConversion3,
     &CtApTb_ConstB.SignalConversion7, &CtApTb_ConstB.SignalConversion4,
     &CtApTb_ConstB.SignalConversion6, &CtApTb_ConstB.SignalConversion7_f,
     &rtb_SignalConversion9, &CtApTb_Y.Fct_TB_FctOffOn_EhvBrkPrk_9Byte,
     &CtApTb_Y.Fct_TB_FctOffOn_EhvBrkSrv_9Byte,
     &CtApTb_Y.Fct_TB_PrkBrkHyd_ST_9Byte, &CtApTb_Y.Fct_TB_PrkBrkHyd_DIAG_9Byte,
     &CtApTb_Y.Fct_TB_BrkSrv_ST_10Byte, &CtApTb_Y.Fct_TB_BrkSrv_DIAG_10Byte,
     &CtApTb_B.TB_RawCore_ref_o7, &CtApTb_Y.TB_Failures_i,
     &CtApTb_Y.Fct_TB_FctByPass_5Byte, &CtApTb_Y.Fct_DHL_Park_Brake_ON,
     &CtApTb_Y.Fct_DHL_Pedal_Brake_ON, &CtApTb_Y.Fct_DHL_Emergency_Brake_ON,
     &CtApTb_Y.Fct_TB_FctDiagAllw_8Byte, &CtApTb_Y.Fct_DHL_Secondary_Brake_ON,
     &CtApTb_Y.Fct_DHL_Brake_OFF, &rtb_TB_RawCore_ref_o16,
     &rtb_TB_RawCore_ref_o17, &rtb_TB_RawCore_ref_o18, &rtb_TB_RawCore_ref_o19,
     &rtb_TB_RawCore_ref_o20, &CtApTb_B.FctOffOn_CmdSRL2,
     &CtApTb_B.TB_RawCore_ref_o22);

  /* End of Outputs for SubSystem: '<Root>/RCtApTb' */

  /* SignalConversion: '<S2>/Sc_HillHoldTestStatus' */
  setHillHoldTestStatus(CtApTb_B.TB_RawCore_ref_o7.HillHoldTestStatus);

  /* SignalConversion: '<S2>/Sc_HydTrailerValveCtrl' */
  setHydTrailerValveCtrl(CtApTb_B.TB_RawCore_ref_o7.HydTrailerParkValveCtrl);

  /* SignalConversion: '<S2>/Sc_TBC2_Counter' */
  setTBC2_Counter(CtApTb_B.TB_RawCore_ref_o7.TBC2_Counter);

  /* SignalConversion: '<S2>/Sc_HydTrailerEmergencyValveProp' */
  setHydTrailerEmergencyValveProp
    (CtApTb_B.TB_RawCore_ref_o7.HydTrailerEmergencyValveProp);

  /* SignalConversion: '<S2>/Sc_TrailBrkPrkEhvCmd' */
  setTrailBrkPrkEhvCmd(rtb_TB_RawCore_ref_o20);

  /* SignalConversion: '<S2>/Sc_TrailBrkSrvEhvCmd' */
  setTrailBrkSrvEhvCmd(CtApTb_B.FctOffOn_CmdSRL2);


  /* End of Outputs for SubSystem: '<Root>/RCtApTb' */

  /* Outputs for Triggered SubSystem: '<S8>/Triggered Subsystem' incorporates:
   *  TriggerPort: '<S15>/Trigger'
   */
  /* Delay: '<S8>/Delay' incorporates:
   *  Constant: '<S15>/Constant1'
   */
  if (CtApTb_DW.Delay_DSTATE && (CtApTb_PrevZCX.TriggeredSubsystem_Trig_ZCE_n !=
       POS_ZCSIG)) {
    setFlagReset_jTBR2_PropB(false);
  }

  CtApTb_PrevZCX.TriggeredSubsystem_Trig_ZCE_n = CtApTb_DW.Delay_DSTATE;

  /* End of Delay: '<S8>/Delay' */
  /* End of Outputs for SubSystem: '<S8>/Triggered Subsystem' */

  /* Outputs for Triggered SubSystem: '<S9>/Triggered Subsystem' incorporates:
   *  TriggerPort: '<S16>/Trigger'
   */
  /* Delay: '<S9>/Delay' incorporates:
   *  Constant: '<S16>/Constant1'
   */
  if (CtApTb_DW.Delay_DSTATE_n && (CtApTb_PrevZCX.TriggeredSubsystem_Trig_ZCE_l
       != POS_ZCSIG)) {
    setFlagReset_jVbmcBrcSystemStatus(false);
  }

  CtApTb_PrevZCX.TriggeredSubsystem_Trig_ZCE_l = CtApTb_DW.Delay_DSTATE_n;

  /* End of Delay: '<S9>/Delay' */
  /* End of Outputs for SubSystem: '<S9>/Triggered Subsystem' */

  /* SignalConversion: '<S2>/Sc_TBC2_Crc' */
  setTBC2_Crc(CtApTb_B.TB_RawCore_ref_o7.TBC2_Crc);

  /* Outputs for Triggered SubSystem: '<S10>/Triggered Subsystem' incorporates:
   *  TriggerPort: '<S17>/Trigger'
   */
  /* Delay: '<S10>/Delay' incorporates:
   *  Constant: '<S17>/Constant1'
   */
  if (CtApTb_DW.Delay_DSTATE_d && (CtApTb_PrevZCX.TriggeredSubsystem_Trig_ZCE !=
       POS_ZCSIG)) {
    setFlagReset_jVbmsBrc_VbmAlive(false);
  }

  CtApTb_PrevZCX.TriggeredSubsystem_Trig_ZCE = CtApTb_DW.Delay_DSTATE_d;

  /* End of Delay: '<S10>/Delay' */
  /* End of Outputs for SubSystem: '<S10>/Triggered Subsystem' */

  /* SignalConversion: '<S2>/Sc_HydTrailerEmergencyValveCtrl' */
  setHydTrailerEmergencyValveCtrl
    (CtApTb_B.TB_RawCore_ref_o7.HydTrailerEmergencyValveCtrl);

  CtApTb_DW.Delay_DSTATE = getFlag_jTBR2_PropB();

  /* Update for Delay: '<S9>/Delay' incorporates:
   *  Update for Inport: '<Root>/jVbmcBrcSystemStatus_ind_b'
   */
  CtApTb_DW.Delay_DSTATE_n = getFlag_jVbmcBrcSystemStatus();

  /* Update for Delay: '<S10>/Delay' incorporates:
   *  Update for Inport: '<Root>/jVbmsBrc_VbmAlive_ind_b'
   */
  CtApTb_DW.Delay_DSTATE_d = getFlag_jVbmsBrc_VbmAlive();

  /* Update for Delay: '<S6>/Delay' */
  CtApTb_DW.Delay_DSTATE_k = false;

/* Model initialize function */
void CtApTis_initialize(void)
{
	 SG_ModuleVersion moduleVersion;
	 moduleVersion.HighValue=((uint8_T)0U);
	 moduleVersion.MiddleValue=((uint8_T)1U);
	 moduleVersion.LowValue=((uint8_T)0U);
	 setOutTisModuleVersion( 0 , moduleVersion.HighValue);
	 setOutTisModuleVersion( 1 , moduleVersion.MiddleValue);
	 setOutTisModuleVersion( 2 ,  moduleVersion.LowValue);

}

/* Model terminate function */
void CtApTis_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
