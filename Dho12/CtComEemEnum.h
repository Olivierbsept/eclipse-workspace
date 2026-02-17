
#ifndef EEM_H_
#define EEM_H_

typedef enum {
  EemState_PowersourceImminentShutdown = 0,
  EemState_PowersourcePendingShutdown = 1,
  EemState_FullSleep = 2,
  EemState_PartialSleep = 3,
  EemState_HiddenWakeUp = 4,
  EemState_OverallWakeUp = 5,
  EemState_ReadyToStartEngine = 8,
  EemState_EnginePreStart = 9,
  EemState_EngineStart = 10,
  EemState_EnginePostStart = 11,
  EemState_GeneratorOn = 16,
  EemState_GeneratorOnHighLoad = 17,
  EemState_EngineStalled = 23,
  EemState_GoToStop = 24,
  EemState_GoToSleep = 25,
  EemState_ReadyToSleep = 26,
  EemState_ShutdownWakeUp = 28,
  EemState_GhostWakeUp = 29,
  EemState_Error = 30,
  EemState_NotAvailable = 31           /* Default value */
} ENU_OverallEemState;

typedef enum {
  AvailableFeedback_None									=  0,
  AvailableFeedback_Full									=  1,
  AvailableFeedback_TerminalNotAvailable					=  2,
  AvailableFeedback_DashboardTerminalNotAvailable			=  3,
  AvailableFeedback_DashboardTerminalDisplayingPartially	=  4,
  AvailableFeedback_DashboardTerminalDisplayNotAvailable	=  5,
  AvailableFeedback_Error									=  6,
  AvailableFeedback_NotAvailable							=  7,
} T_AvailableFeedback;

typedef enum {
	DiagInhibit_Allowed = 0,
	DiagInhibit_NotAllowed = 1,
	DiagInhibit_Error = 2,
	DiagInhibit_NotAvailable = 3,
} T_DiagInhibit;
#endif /* EEM_ */
