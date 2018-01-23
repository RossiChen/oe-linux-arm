#ifndef QUECTEL_FEATURES_CONFIG_H
#define QUECTEL_FEATURES_CONFIG_H

#include "quectel-buildconfig-gen.h"

#if defined (__QUECTEL_PROJECT_EC20C_FA__) || defined (__QUECTEL_PROJECT_EC20CE_FA__) || defined (__QUECTEL_PROJECT_EC20CE_FD__) || defined (__QUECTEL_PROJECT_EC20C_FD__) \
    || defined (__QUECTEL_PROJECT_EC20C_FT__) || defined (__QUECTEL_PROJECT_EC21C_FD__) || defined (__QUECTEL_PROJECT_EC20CFD_HIK__) \
    || defined (__QUECTEL_PROJECT_EC20C_FTB__)
#define QUEC_RF_EC25C
#elif defined (__QUECTEL_PROJECT_EC25E__) || defined (__QUECTEL_PROJECT_EC21E__)
#define QUEC_RF_EC25E
#elif defined (__QUECTEL_PROJECT_EC21AUT__) || defined (__QUECTEL_PROJECT_EC21AUTL__) || defined (__QUECTEL_PROJECT_EC25AUT__) || defined (__QUECTEL_PROJECT_EC25AUTL__)
#define QUEC_RF_EC25AUT
#elif defined (__QUECTEL_PROJECT_EC25AU__) || defined (__QUECTEL_PROJECT_EC21AU__) || defined (__QUECTEL_PROJECT_R62_EC25AU__)
#define QUEC_RF_EC25AU
#elif defined (__QUECTEL_PROJECT_EC21AUV__)
#define QUEC_RF_EC21AUV
#elif defined (__QUECTEL_PROJECT_EC21A__) || defined (__QUECTEL_PROJECT_EC25A__) || defined (__QUECTEL_PROJECT_EC21AL__) || defined (__QUECTEL_PROJECT_R62_EC25A__)
#define QUEC_RF_EC21A
#elif defined (__QUECTEL_PROJECT_EC21AS__)
#define QUEC_RF_EC21AS
#elif defined (__QUECTEL_PROJECT_EC21V__) || defined (__QUECTEL_PROJECT_EC21VD__) || defined (__QUECTEL_PROJECT_EC25VD__) || defined (__QUECTEL_PROJECT_EC25V__)
#define QUEC_RF_EC21V
#elif defined (__QUECTEL_PROJECT_EC20C_GW__) || defined (__QUECTEL_PROJECT_EC20CE_GW__)
#define QUEC_RF_EC25C
#define QUECTEL_EC25_GW_FEATURE 
#elif defined (__QUECTEL_PROJECT_EC21CT__)
#define QUEC_RF_EC21CT
#elif defined (__QUECTEL_PROJECT_EC21KL__)
#define QUEC_RF_EC21KL
#elif defined (__QUECTEL_PROJECT_EC25J__) || defined (__QUECTEL_PROJECT_EC21J__)
#define QUEC_RF_EC25J
#elif defined (__QUECTEL_PROJECT_EC20CE_CT__)
#define QUEC_RF_EC25C
#define QUECTEL_CTCC_SUPPORT
#define QUECTEL_CTCC_PRIVATE
#elif defined (__QUECTEL_PROJECT_EG91E__) || defined (__QUECTEL_PROJECT_EG95E__) 
#define QUEC_RF_EG91E
#elif defined(__QUECTEL_PROJECT_EC21NA__) || defined (__QUECTEL_PROJECT_EG91NA__) || defined (__QUECTEL_PROJECT_EG95NA__)
#define QUEC_RF_EC21NA
#elif defined (__QUECTEL_PROJECT_EG91NA__) || defined (__QUECTEL_PROJECT_EG95NA__)
#define QUEC_RF_EG91NA
#else
#########ERROR PROJECT NAME###########
#endif


#ifndef QUEC_RF_EC25C
#define QUECTEL_TTS_LANG_ENG
#endif

#define QUECTEL_MBIM_FEATURE

#ifdef QUECTEL_MBIM_FEATURE
#define QUECTEL_MBIM_LOG
#endif
#define QUECTEL_CONTROL_ICCID_DISPLAY //lory2017/05/31 fix QC3655 if ICCID include hex A to F ,cannot display content after that
#define QUECTEL_URC_SUPPORT
#endif
