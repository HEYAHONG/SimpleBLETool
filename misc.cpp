
#include "misc.h"
#include "gatt_profile_uuid.h"

typedef struct
{
    uint16_t uuid;
    const char * desc;
} BLEUuidDesc_t;

#define MicroToBLEUuidDesc(x) {x,#x}

static const BLEUuidDesc_t desc_array[]=
{
//Gatt服务
    MicroToBLEUuidDesc(GAP_SERVICE_UUID),//                           0x1800 // Generic Access Profile
    MicroToBLEUuidDesc(GATT_SERVICE_UUID),//                          0x1801 // Generic Attribute Profile
    MicroToBLEUuidDesc(IMMEDIATE_ALERT_SERV_UUID),//       0x1802  // Immediate Alert
    MicroToBLEUuidDesc(LINK_LOSS_SERV_UUID),//              0x1803  // Link Loss
    MicroToBLEUuidDesc(TX_PWR_LEVEL_SERV_UUID),//           0x1804  // Tx Power
    MicroToBLEUuidDesc(CURRENT_TIME_SERV_UUID ),//          0x1805  // Current Time Service
    MicroToBLEUuidDesc(REF_TIME_UPDATE_SERV_UUID),//        0x1806  // Reference Time Update Service
    MicroToBLEUuidDesc(NEXT_DST_CHANGE_SERV_UUID),//       0x1807  // Next DST Change Service
    MicroToBLEUuidDesc(GLUCOSE_SERV_UUID),//               0x1808  // Glucose
    MicroToBLEUuidDesc(THERMOMETER_SERV_UUID),//           0x1809  // Health Thermometer
    MicroToBLEUuidDesc(DEVINFO_SERV_UUID),//               0x180A  // Device Information
    MicroToBLEUuidDesc(NWA_SERV_UUID),//                  0x180B  // Network Availability
    MicroToBLEUuidDesc(HEARTRATE_SERV_UUID),//             0x180D  // Heart Rate
    MicroToBLEUuidDesc(PHONE_ALERT_STS_SERV_UUID),//        0x180E  // Phone Alert Status Service
    MicroToBLEUuidDesc(BATT_SERV_UUID),//                   0x180F  // Battery Service
    MicroToBLEUuidDesc(BLOODPRESSURE_SERV_UUID),//         0x1810  // Blood Pressure
    MicroToBLEUuidDesc(ALERT_NOTIF_SERV_UUID),//            0x1811  // Alert Notification Service
    MicroToBLEUuidDesc(HID_SERV_UUID),//                   0x1812  // Human Interface Device
    MicroToBLEUuidDesc(SCAN_PARAM_SERV_UUID ),//            0x1813  // Scan Parameters
    MicroToBLEUuidDesc(RSC_SERV_UUID),//                  0x1814  // Running Speed and Cadence
    MicroToBLEUuidDesc(CSC_SERV_UUID),//                   0x1816  // Cycling Speed and Cadence
    MicroToBLEUuidDesc(CYCPWR_SERV_UUID),//                0x1818  // Cycling Power
    MicroToBLEUuidDesc(LOC_NAV_SERV_UUID),//               0x1819  // Location and Navigation

//Gatt Declaration
    MicroToBLEUuidDesc(GATT_PRIMARY_SERVICE_UUID),//                  0x2800 // Primary Service
    MicroToBLEUuidDesc(GATT_SECONDARY_SERVICE_UUID),//                0x2801 // Secondary Service
    MicroToBLEUuidDesc(GATT_INCLUDE_UUID),//                          0x2802 // Include
    MicroToBLEUuidDesc(GATT_CHARACTER_UUID),//                        0x2803 // Characteristic

//Gatt特征
    MicroToBLEUuidDesc(DEVICE_NAME_UUID),//                           0x2A00 // Device Name
    MicroToBLEUuidDesc(APPEARANCE_UUID),//                            0x2A01 // Appearance
    MicroToBLEUuidDesc(PERI_PRIVACY_FLAG_UUID),//                     0x2A02 // Peripheral Privacy Flag
    MicroToBLEUuidDesc(RECONNECT_ADDR_UUID),//                        0x2A03 // Reconnection Address
    MicroToBLEUuidDesc(PERI_CONN_PARAM_UUID),//                       0x2A04 // Peripheral Preferred Connection Parameters
    MicroToBLEUuidDesc(SERVICE_CHANGED_UUID),//                       0x2A05 // Service Changed
    MicroToBLEUuidDesc(ALERT_LEVEL_UUID),//                0x2A06  // Alert Level
    MicroToBLEUuidDesc(TX_PWR_LEVEL_UUID),//               0x2A07  // Tx Power Level
    MicroToBLEUuidDesc(DATE_TIME_UUID),//                 0x2A08  // Date Time
    MicroToBLEUuidDesc(DAY_OF_WEEK_UUID),//               0x2A09  // Day of Week
    MicroToBLEUuidDesc(DAY_DATE_TIME_UUID),//              0x2A0A  // Day Date Time
    MicroToBLEUuidDesc(EXACT_TIME_256_UUID),//              0x2A0C  // Exact Time 256
    MicroToBLEUuidDesc(DST_OFFSET_UUID),//                0x2A0D  // DST Offset
    MicroToBLEUuidDesc(TIME_ZONE_UUID),//                 0x2A0E  // Time Zone
    MicroToBLEUuidDesc(LOCAL_TIME_INFO_UUID),//           0x2A0F  // Local Time Information
    MicroToBLEUuidDesc(TIME_WITH_DST_UUID),//              0x2A11  // Time with DST
    MicroToBLEUuidDesc(TIME_ACCURACY_UUID),//              0x2A12  // Time Accuracy
    MicroToBLEUuidDesc(TIME_SOURCE_UUID),//               0x2A13  // Time Source
    MicroToBLEUuidDesc(REF_TIME_INFO_UUID),//             0x2A14  // Reference Time Information
    MicroToBLEUuidDesc(TIME_UPDATE_CTRL_PT_UUID),//        0x2A16  // Time Update Control Point
    MicroToBLEUuidDesc(TIME_UPDATE_STATE_UUID),//          0x2A17  // Time Update State
    MicroToBLEUuidDesc(GLUCOSE_MEAS_UUID),//               0x2A18  // Glucose Measurement
    MicroToBLEUuidDesc(BATT_LEVEL_UUID),//                  0x2A19  // Battery Level
    MicroToBLEUuidDesc(TEMP_MEAS_UUID),//                  0x2A1C  // Temperature Measurement
    MicroToBLEUuidDesc(TEMP_TYPE_UUID),//                  0x2A1D  // Temperature Type
    MicroToBLEUuidDesc(IMEDIATE_TEMP_UUID),//              0x2A1E  // Intermediate Temperature
    MicroToBLEUuidDesc(MEAS_INTERVAL_UUID),//              0x2A21  // Measurement Interval
    MicroToBLEUuidDesc(BOOT_KEY_INPUT_UUID),//             0x2A22  // Boot Keyboard Input Report
    MicroToBLEUuidDesc(SYSTEM_ID_UUID),//                  0x2A23  // System ID
    MicroToBLEUuidDesc(MODEL_NUMBER_UUID),//               0x2A24  // Model Number String
    MicroToBLEUuidDesc(SERIAL_NUMBER_UUID),//              0x2A25  // Serial Number String
    MicroToBLEUuidDesc(FIRMWARE_REV_UUID),//               0x2A26  // Firmware Revision String
    MicroToBLEUuidDesc(HARDWARE_REV_UUID),//               0x2A27  // Hardware Revision String
    MicroToBLEUuidDesc(SOFTWARE_REV_UUID),//               0x2A28  // Software Revision String
    MicroToBLEUuidDesc(MANUFACTURER_NAME_UUID ),//          0x2A29  // Manufacturer Name String
    MicroToBLEUuidDesc(IEEE_11073_CERT_DATA_UUID  ),//      0x2A2A  // IEEE 11073-20601 Regulatory Certification Data List
    MicroToBLEUuidDesc(CURRENT_TIME_UUID),//                0x2A2B  // Current Time
    MicroToBLEUuidDesc(SCAN_REFRESH_UUID),//              0x2A31  // Scan Refresh
    MicroToBLEUuidDesc(BOOT_KEY_OUTPUT_UUID),//            0x2A32  // Boot Keyboard Output Report
    MicroToBLEUuidDesc(BOOT_MOUSE_INPUT_UUID),//          0x2A33  // Boot Mouse Input Report
    MicroToBLEUuidDesc(GLUCOSE_CONTEXT_UUID),//            0x2A34  // Glucose Measurement Context
    MicroToBLEUuidDesc(BLOODPRESSURE_MEAS_UUID),//         0x2A35  // Blood Pressure Measurement
    MicroToBLEUuidDesc(IMEDIATE_CUFF_PRESSURE_UUID),//     0x2A36  // Intermediate Cuff Pressure
    MicroToBLEUuidDesc(HEARTRATE_MEAS_UUID),//             0x2A37  // Heart Rate Measurement
    MicroToBLEUuidDesc(BODY_SENSOR_LOC_UUID),//            0x2A38  // Body Sensor Location
    MicroToBLEUuidDesc(HEARTRATE_CTRL_PT_UUID),//          0x2A39  // Heart Rate Control Point
    MicroToBLEUuidDesc(NETWORK_AVAIL_UUID),//             0x2A3E  // Network Availability
    MicroToBLEUuidDesc(ALERT_STATUS_UUID),//               0x2A3F  // Alert Status
    MicroToBLEUuidDesc(RINGER_CTRL_PT_UUID),//            0x2A40  // Ringer Control Point
    MicroToBLEUuidDesc(RINGER_SETTING_UUID),//              0x2A41  // Ringer Setting
    MicroToBLEUuidDesc(ALERT_CAT_ID_BMASK_UUID ),//         0x2A42  // Alert Category ID Bit Mask
    MicroToBLEUuidDesc(ALERT_CAT_ID_UUID),//               0x2A43  // Alert Category ID
    MicroToBLEUuidDesc(ALERT_NOTIF_CTRL_PT_UUID),//        0x2A44  // Alert Notification Control Point
    MicroToBLEUuidDesc(UNREAD_ALERT_STATUS_UUID),//        0x2A45  // Unread Alert Status
    MicroToBLEUuidDesc(NEW_ALERT_UUID),//                  0x2A46  // New Alert
    MicroToBLEUuidDesc(SUP_NEW_ALERT_CAT_UUID),//          0x2A47  // Supported New Alert Category
    MicroToBLEUuidDesc(SUP_UNREAD_ALERT_CAT_UUID ),//       0x2A48  // Supported Unread Alert Category
    MicroToBLEUuidDesc(BLOODPRESSURE_FEATURE_UUID ),//      0x2A49  // Blood Pressure Feature
    MicroToBLEUuidDesc(HID_INFORMATION_UUID  ),//           0x2A4A  // HID Information
    MicroToBLEUuidDesc(REPORT_MAP_UUID    ),//              0x2A4B  // Report Map
    MicroToBLEUuidDesc(HID_CTRL_PT_UUID ),//                0x2A4C  // HID Control Point
    MicroToBLEUuidDesc(REPORT_UUID ),//                     0x2A4D  // Report
    MicroToBLEUuidDesc(PROTOCOL_MODE_UUID  ),//             0x2A4E  // Protocol Mode
    MicroToBLEUuidDesc(SCAN_INTERVAL_WINDOW_UUID),//        0x2A4F  // Scan Interval Window
    MicroToBLEUuidDesc(PNP_ID_UUID),//                    0x2A50  // PnP ID
    MicroToBLEUuidDesc(GLUCOSE_FEATURE_UUID),//           0x2A51  // Glucose Feature
    MicroToBLEUuidDesc(RECORD_CTRL_PT_UUID),//             0x2A52  // Record Access Control Point
    MicroToBLEUuidDesc(RSC_MEAS_UUID),//                  0x2A53  // RSC Measurement
    MicroToBLEUuidDesc(RSC_FEATURE_UUID),//                 0x2A54  // RSC Feature
    MicroToBLEUuidDesc(SC_CTRL_PT_UUID ),//                 0x2A55  // SC Control Point
    MicroToBLEUuidDesc(CSC_MEAS_UUID ),//                   0x2A5B  // CSC Measurement
    MicroToBLEUuidDesc(CSC_FEATURE_UUID ),//                0x2A5C  // CSC Feature
    MicroToBLEUuidDesc(SENSOR_LOC_UUID  ),//                0x2A5D  // Sensor Location
    MicroToBLEUuidDesc(CYCPWR_MEAS_UUID ),//                0x2A63  // Cycling Power Measurement
    MicroToBLEUuidDesc(CYCPWR_VECTOR_UUID ),//              0x2A64  // Cycling Power Vector
    MicroToBLEUuidDesc(CYCPWR_FEATURE_UUID),//            0x2A65  // Cycling Power Feature
    MicroToBLEUuidDesc(CYCPWR_CTRL_PT_UUID),//            0x2A66  // Cycling Power Control Point
    MicroToBLEUuidDesc(LOC_SPEED_UUID),//                   0x2A67  // Location and Speed
    MicroToBLEUuidDesc(NAV_UUID),//                    0x2A68  // Navigation
    MicroToBLEUuidDesc(POS_QUALITY_UUID),//                0x2A69  // Position Quality
    MicroToBLEUuidDesc(LN_FEATURE_UUID),//                0x2A6A  // LN Feature
    MicroToBLEUuidDesc(LN_CTRL_PT_UUID),//                0x2A6B  // LN Control Point
//Gatt Descriptor
    MicroToBLEUuidDesc(GATT_CHAR_EXT_PROPS_UUID),//                   0x2900 // Characteristic Extended Properties
    MicroToBLEUuidDesc(GATT_CHAR_USER_DESC_UUID),//                  0x2901 // Characteristic User Description
    MicroToBLEUuidDesc(GATT_CLIENT_CHAR_CFG_UUID),//                  0x2902 // Client Characteristic Configuration
    MicroToBLEUuidDesc(GATT_SERV_CHAR_CFG_UUID),//                    0x2903 // Server Characteristic Configuration
    MicroToBLEUuidDesc(GATT_CHAR_FORMAT_UUID),//                      0x2904 // Characteristic Presentation Format
    MicroToBLEUuidDesc(GATT_CHAR_AGG_FORMAT_UUID),//                  0x2905 // Characteristic Aggregate Format
    MicroToBLEUuidDesc(GATT_VALID_RANGE_UUID),//                      0x2906 // Valid Range
    MicroToBLEUuidDesc(GATT_EXT_REPORT_REF_UUID),//                   0x2907 // External Report Reference Descriptor
    MicroToBLEUuidDesc(GATT_REPORT_REF_UUID),//                       0x2908 // Report Reference Descriptor

//Gatt Unit
    MicroToBLEUuidDesc(GATT_UNITLESS_UUID),//                    0x2700  // <Symbol>, <Expressed in terms of SI base units>
    MicroToBLEUuidDesc(GATT_UNIT_LENGTH_METER_UUID),//           0x2701  // m, m
    MicroToBLEUuidDesc(GATT_UNIT_MASS_KGRAM_UUID),//             0x2702  // kg, kg
    MicroToBLEUuidDesc(GATT_UNIT_TIME_SECOND_UUID),//            0x2703  // s, s
    MicroToBLEUuidDesc(GATT_UNIT_ELECTRIC_CURRENT_A_UUID),//     0x2704  // A, A
    MicroToBLEUuidDesc(GATT_UNIT_THERMODYN_TEMP_K_UUID),//       0x2705  // K, K
    MicroToBLEUuidDesc(GATT_UNIT_AMOUNT_SUBSTANCE_M_UUID),//     0x2706  // mol, mol
    MicroToBLEUuidDesc(GATT_UNIT_LUMINOUS_INTENSITY_C_UUID),//   0x2707  // cd, cd
    MicroToBLEUuidDesc(GATT_UNIT_AREA_SQ_MTR_UUID),//            0x2710  // m^2, m^2
    MicroToBLEUuidDesc(GATT_UNIT_VOLUME_CUBIC_MTR_UUID),//       0x2711  // m^3, m^3
    MicroToBLEUuidDesc(GATT_UNIT_VELOCITY_MPS_UUID),//           0x2712  // m/s, m s^-1
    MicroToBLEUuidDesc(GATT_UNIT_ACCELERATION_MPS_SQ_UUID),//    0x2713  // m/s^2, m s^-2
    MicroToBLEUuidDesc(GATT_UNIT_WAVENUMBER_RM_UUID),//          0x2714  // ? m^-1
    MicroToBLEUuidDesc(GATT_UNIT_DENSITY_KGPCM_UUID),//          0x2715  // p, kg m^-3
    MicroToBLEUuidDesc(GATT_UNIT_SURFACE_DENSITY_KGPSM_UUID),//  0x2716  // pA, kg m^-2
    MicroToBLEUuidDesc(GATT_UNIT_SPECIFIC_VOLUME_CMPKG_UUID),//  0x2717  // v, m^3 kg^-1
    MicroToBLEUuidDesc(GATT_UNIT_CURRENT_DENSITY_APSM_UUID),//   0x2718  // j, A m^-2
    MicroToBLEUuidDesc(GATT_UNIT_MAG_FIELD_STRENGTH_UUID),//     0x2719  // H, A m
    MicroToBLEUuidDesc(GATT_UNIT_AMOUNT_CONC_MPCM_UUID),//       0x271A  // c, mol m^-3
    MicroToBLEUuidDesc(GATT_UNIT_MASS_CONC_KGPCM_UUID),//        0x271B  // c, kg m^-3
    MicroToBLEUuidDesc(GATT_UNIT_LUMINANCE_CPSM_UUID),//         0x271C  // Lv, cd m^-2
    MicroToBLEUuidDesc(GATT_UNIT_REFRACTIVE_INDEX_UUID),//       0x271D  // n, 1
    MicroToBLEUuidDesc(GATT_UNIT_RELATIVE_PERMEABLILTY_UUID),//  0x271E  // u, 1
    MicroToBLEUuidDesc(GATT_UNIT_PLANE_ANGLE_RAD_UUID),//        0x2720  // rad, m m-1
    MicroToBLEUuidDesc(GATT_UNIT_SOLID_ANGLE_STERAD_UUID),//    0x2721  // sr, m2 m-2
    MicroToBLEUuidDesc(GATT_UNIT_FREQUENCY_HTZ_UUID),//          0x2722  // Hz, s-1
    MicroToBLEUuidDesc(GATT_UNIT_FORCE_NEWTON_UUID),//           0x2723  // N, m kg s-2
    MicroToBLEUuidDesc(GATT_UNIT_PRESSURE_PASCAL_UUID),//       0x2724  // Pa, N/m2 = m2 kg s-2
    MicroToBLEUuidDesc(GATT_UNIT_ENERGY_JOULE_UUID),//          0x2725  // J, N m = m2 kg s-2
    MicroToBLEUuidDesc(GATT_UNIT_POWER_WATT_UUID),//            0x2726  // W, J/s = m2 kg s-3
    MicroToBLEUuidDesc(GATT_UNIT_E_CHARGE_C_UUID),//            0x2727  // C, sA
    MicroToBLEUuidDesc(GATT_UNIT_E_POTENTIAL_DIF_V_UUID),//      0x2728  // V, W/A = m2 kg s-3 A-1
    MicroToBLEUuidDesc(GATT_UNIT_CELSIUS_TEMP_DC_UUID),//        0x272F  // oC, t/oC = T/K - 273.15
    MicroToBLEUuidDesc(GATT_UNIT_TIME_MINUTE_UUID),//            0x2760  // min, 60 s
    MicroToBLEUuidDesc(GATT_UNIT_TIME_HOUR_UUID),//             0x2761  // h, 3600 s
    MicroToBLEUuidDesc(GATT_UNIT_TIME_DAY_UUID),//              0x2762  // d, 86400 s
    MicroToBLEUuidDesc(GATT_UNIT_PLANE_ANGLE_DEGREE_UUID),//     0x2763  // o, (pi/180) rad
    MicroToBLEUuidDesc(GATT_UNIT_PLANE_ANGLE_MINUTE_UUID),//     0x2764  // ', (pi/10800) rad
    MicroToBLEUuidDesc(GATT_UNIT_PLANE_ANGLE_SECOND_UUID),//    0x2765  // '', (pi/648000) rad
    MicroToBLEUuidDesc(GATT_UNIT_AREA_HECTARE_UUID),//          0x2766  // ha, 10^4 m^2
    MicroToBLEUuidDesc(GATT_UNIT_VOLUME_LITRE_UUID),//         0x2767  // l, 10^-3 m^3
    MicroToBLEUuidDesc(GATT_UNIT_MASS_TONNE_UUID),//            0x2768  // t, 10^3 kg
    MicroToBLEUuidDesc(GATT_UINT_LENGTH_YARD_UUID),//           0x27A0  // yd, 0.9144 m
    MicroToBLEUuidDesc(GATT_UNIT_LENGTH_PARSEC_UUID),//         0x27A1  // pc, 3.085678 ?1016 m
    MicroToBLEUuidDesc(GATT_UNIT_LENGTH_INCH_UUID),//          0x27A2  // in, 0.0254 m
    MicroToBLEUuidDesc(GATT_UNIT_LENGTH_FOOT_UUID),//           0x27A3  // ft, 0.3048 m
    MicroToBLEUuidDesc(GATT_UNIT_LENGTH_MILE_UUID),//           0x27A4  // mi, 1609.347 m
    MicroToBLEUuidDesc(GATT_UNIT_PRESSURE_PFPSI_UUID),//        0x27A5  // psi, 6.894757 ?103 Pa
    MicroToBLEUuidDesc(GATT_UNIT_VELOCITY_KMPH_UUID),//         0x27A6  // km/h, 0.2777778 m^s-1
    MicroToBLEUuidDesc(GATT_UNIT_VELOCITY_MPH_UUID),//          0x27A7  // mi/h, 0.44704 m^ s-1
    MicroToBLEUuidDesc(GATT_UNIT_ANGULAR_VELOCITY_RPM_UUID),//  0x27A8  // r/min, 0.1047198 rad s-1
    MicroToBLEUuidDesc(GATT_UNIT_ENERGY_GCAL_UUID),//           0x27A9  //
    MicroToBLEUuidDesc(GATT_UNIT_ENERGY_KCAL_UUID),//           0x27AA  // kcal, 4190.02 J
    MicroToBLEUuidDesc(GATT_UNIT_ENERGY_KWH_UUID),//             0x27AB  // kWh, 3600000 J
    MicroToBLEUuidDesc(GATT_UNIT_THERMODYN_TEMP_DF_UUID),//     0x27AC  // oF, t/oF = T/K ?1.8 - 459.67
    MicroToBLEUuidDesc(GATT_UNIT_PERCENTAGE_UUID),//             0x27AD  // %
    MicroToBLEUuidDesc(GATT_UNIT_PER_MILE_UUID),//              0x27AE  //
    MicroToBLEUuidDesc(GATT_UNIT_PERIOD_BPM_UUID),//           0x27AF  //
    MicroToBLEUuidDesc(GATT_UNIT_E_CHARGE_AH_UUID),//           0x27B0  //
    MicroToBLEUuidDesc(GATT_UNIT_MASS_DENSITY_MGPD_UUID),//      0x27B1  //
    MicroToBLEUuidDesc(GATT_UNIT_MASS_DENSITY_MMPL_UUID),//     0x27B2  //
    MicroToBLEUuidDesc(GATT_UNIT_TIME_YEAR_UUID ),//            0x27B3  //
    MicroToBLEUuidDesc(GATT_UNIT_TIME_MONTH_UUID),//             0x27B4  //

// Simple Profile Service
    MicroToBLEUuidDesc(SIMPLEPROFILE_SERV_UUID),//               0xFFF0

// Simple Profile Characteristic
    MicroToBLEUuidDesc(SIMPLEPROFILE_CHAR1_UUID),//            0xFFF1
    MicroToBLEUuidDesc(SIMPLEPROFILE_CHAR2_UUID),//            0xFFF2
    MicroToBLEUuidDesc(SIMPLEPROFILE_CHAR3_UUID),//            0xFFF3
    MicroToBLEUuidDesc(SIMPLEPROFILE_CHAR4_UUID),//            0xFFF4
    MicroToBLEUuidDesc(SIMPLEPROFILE_CHAR5_UUID),//            0xFFF5
    MicroToBLEUuidDesc(SIMPLEPROFILE_CHAR6_UUID)//            0xFFF6

};


std::string GetBLEUuidDescByShortUuid(uint16_t shortuuid)
{
    for(size_t i=0; i<(sizeof(desc_array)/sizeof(desc_array[0])); i++)
    {
        if(desc_array[i].uuid==shortuuid)
        {
            return desc_array[i].desc;
        }
    }
    return "";
}

bool IsBLEShortUUID(std::string uuid)
{
    if(uuid.empty())
    {
        return false;
    }
    std::transform(uuid.begin(),uuid.end(),uuid.begin(),tolower);

    std::string short_uuid_template="0000xxxx-0000-1000-8000-00805F9B34FB";
    std::transform(short_uuid_template.begin(),short_uuid_template.end(),short_uuid_template.begin(),tolower);

    uuid.replace(4,4,"xxxx");

    return uuid==short_uuid_template;
}
