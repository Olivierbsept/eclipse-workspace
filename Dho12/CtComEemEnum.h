
#ifndef EEM_H_
#define EEM_H_

enum ENU_OverallEemState_TIS {
  TIS_EemState_ReadyToStartEngine = 8,
  TIS_EemState_GeneratorOn = 16,
  TIS_EemState_GeneratorOnHighLoad = 17,
  TIS_EemState_NotAvailable = 31           /* Default value */
} ;
#endif /* EEM_ */
