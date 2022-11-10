#include "jni.h"
#include <stdio.h>
#include "cJSON.h"
#include "sha256.h"
#include "dl_iso8583.h"
#include "dl_iso8583_defs_1987.h"
#include "dl_utils.h"
#include "main.h"
#include "time.h"

JNIEXPORT jstring JNICALL
Java_com_besl_nibss_epms_ISO8583_getVersion( JNIEnv *env, jobject thisObj) {

    const unsigned char completeVersion[] =
            {
                    VERSION_MAJOR_INIT,
                    '.',
                    VERSION_MINOR_INIT,
                    '.',
                    VERSION_PATCH_INIT,
                    /*'-', 'V', '-',
                    BUILD_YEAR_CH0, BUILD_YEAR_CH1, BUILD_YEAR_CH2, BUILD_YEAR_CH3,
                    '-',
                    BUILD_MONTH_CH0, BUILD_MONTH_CH1,
                    '-',
                    BUILD_DAY_CH0, BUILD_DAY_CH1,
                    'T',
                    BUILD_HOUR_CH0, BUILD_HOUR_CH1,
                    ':',
                    BUILD_MIN_CH0, BUILD_MIN_CH1,
                    ':',
                    BUILD_SEC_CH0, BUILD_SEC_CH1,*/
                    '\0'
            };

    return (*env)->NewStringUTF(env, completeVersion);
}

JNIEXPORT jstring JNICALL
Java_com_besl_nibss_epms_ISO8583_packEPMSISO8583Message( JNIEnv *env, jobject thisObj, jstring fields, jstring key) {

    DL_ISO8583_HANDLER isoHandler;
    DL_ISO8583_MSG isoMsg;
    DL_UINT8 buf[MAX_DATASIZE];
    DL_UINT16 bufSize;
    DL_ERR err = kDL_ERR_NONE;
    cJSON *cjsonObject, *cjson;
    char chash[65];
    int maxfld;
    int iRet;
    char pcOutBuffer[MAX_DATASIZE];

    DL_ISO8583_DEFS_1987_GetHandler(&isoHandler);

    /* initialise ISO message */
    DL_ISO8583_MSG_Init(NULL, 0, &isoMsg);

    maxfld = 0;

    const char * jsonfields = (*env)->GetStringUTFChars(env, fields, 0);
    const char * mkey = (*env)->GetStringUTFChars(env, key, 0);

    cjsonObject = cJSON_Parse(jsonfields);
    if (!cjsonObject) {
        return NULL;
    }

    //(*env)->ReleaseStringUTFChars(env,fields, jsonfields);//clear the data from the memory after using

    cjson = cJSON_GetObjectItem(cjsonObject, "0");
    if (cjson != NULL) {
        maxfld = atoi("0");
        (void) DL_ISO8583_MSG_SetField_Str(0, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //PAN
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "2");
    if (cjson != NULL) {
        maxfld = atoi("2");
        (void) DL_ISO8583_MSG_SetField_Str(2, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //PAN
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "3");
    if (cjson != NULL) {
        maxfld = atoi("3");
        (void) DL_ISO8583_MSG_SetField_Str(3, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //processing code
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "4");
    if (cjson != NULL) {
        maxfld = atoi("4");
        (void) DL_ISO8583_MSG_SetField_Str(4, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //amount
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "7");
    if (cjson != NULL) {
        maxfld = atoi("7");
        (void) DL_ISO8583_MSG_SetField_Str(7, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //PAN
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "11");
    if (cjson != NULL) {
        maxfld = atoi("11");
        (void) DL_ISO8583_MSG_SetField_Str(11, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //PAN
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "12");
    if (cjson != NULL) {
        maxfld = atoi("12");
        (void) DL_ISO8583_MSG_SetField_Str(12, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //PAN
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "13");
    if (cjson != NULL) {
        maxfld = atoi("13");
        (void) DL_ISO8583_MSG_SetField_Str(13, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //PAN
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "14");
    if (cjson != NULL) {
        maxfld = atoi("14");
        (void) DL_ISO8583_MSG_SetField_Str(14, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //PAN
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "18");
    if (cjson != NULL) {
        maxfld = atoi("18");
        (void) DL_ISO8583_MSG_SetField_Str(18, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //PAN
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "22");
    if (cjson != NULL) {
        maxfld = atoi("22");
        (void) DL_ISO8583_MSG_SetField_Str(22, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //POS Entry Mode
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "23");
    if (cjson != NULL) {
        maxfld = atoi("23");
        (void) DL_ISO8583_MSG_SetField_Str(23, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //Card Sequence Number
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "25");
    if (cjson != NULL) {
        maxfld = atoi("25");
        (void) DL_ISO8583_MSG_SetField_Str(25, (const DL_UINT8 *)cjson->valuestring, &isoMsg);
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "26");
    if (cjson != NULL) {
        maxfld = atoi("26");
        (void) DL_ISO8583_MSG_SetField_Str(26, (const DL_UINT8 *)cjson->valuestring, &isoMsg);
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "28");
    if (cjson != NULL) {
        maxfld = atoi("28");
        (void) DL_ISO8583_MSG_SetField_Str(28, (const DL_UINT8 *)cjson->valuestring, &isoMsg);
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "32");
    if (cjson != NULL) {
        maxfld = atoi("32");
        (void) DL_ISO8583_MSG_SetField_Str(32, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //BIN
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "35");
    if (cjson != NULL) {
        maxfld = atoi("35");
        (void) DL_ISO8583_MSG_SetField_Str(35, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //Track 2 Data
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "37");
    if (cjson != NULL) {
        maxfld = atoi("37");
        (void) DL_ISO8583_MSG_SetField_Str(37, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //Retrieval Reference Number
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "40");
    if (cjson != NULL) {
        maxfld = atoi("40");
        (void) DL_ISO8583_MSG_SetField_Str(40, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //Service Restriction Code (Card Service Code)
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "41");
    if (cjson != NULL) {
        maxfld = atoi("41");
        (void) DL_ISO8583_MSG_SetField_Str(41, (const DL_UINT8 *)cjson->valuestring, &isoMsg);
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "42");
    if (cjson != NULL) {
        maxfld = atoi("42");
        (void) DL_ISO8583_MSG_SetField_Str(42, (const DL_UINT8 *)cjson->valuestring, &isoMsg);
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "43");
    if (cjson != NULL) {
        maxfld = atoi("43");
        (void) DL_ISO8583_MSG_SetField_Str(43, (const DL_UINT8 *)cjson->valuestring, &isoMsg);
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "49");
    if (cjson != NULL) {
        maxfld = atoi("49");
        (void) DL_ISO8583_MSG_SetField_Str(49, (const DL_UINT8 *)cjson->valuestring, &isoMsg);
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "52");
    if (cjson != NULL) {
        maxfld = atoi("52");
        (void) DL_ISO8583_MSG_SetField_Str(52, (const DL_UINT8 *)cjson->valuestring, &isoMsg);//PIN Data
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "54");
    if (cjson != NULL) {
        maxfld = atoi("54");
        (void) DL_ISO8583_MSG_SetField_Str(54, (const DL_UINT8 *)cjson->valuestring, &isoMsg);//cashback amount
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "55");
    if (cjson != NULL) {
        maxfld = atoi("55");
        (void) DL_ISO8583_MSG_SetField_Str(55, (const DL_UINT8 *)cjson->valuestring, &isoMsg);//Integrated Circuit Card System Related Data
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "62");
    if (cjson != NULL) {
        maxfld = atoi("62");
        (void) DL_ISO8583_MSG_SetField_Str(62, (const DL_UINT8 *)cjson->valuestring, &isoMsg); //PAN
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "90");
    if (cjson != NULL) {
        maxfld = atoi("90");
        (void) DL_ISO8583_MSG_SetField_Str(90, (const DL_UINT8 *)cjson->valuestring, &isoMsg);//Amount, Replacement
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "95");
    if (cjson != NULL) {
        maxfld = atoi("95");
        (void) DL_ISO8583_MSG_SetField_Str(95, (const DL_UINT8 *)cjson->valuestring, &isoMsg);//Amount, Replacement
    }
    cjson = cJSON_GetObjectItem(cjsonObject, "123");
    if (cjson != NULL) {
        maxfld = atoi("123");
        (void) DL_ISO8583_MSG_SetField_Str(123, (const DL_UINT8 *)cjson->valuestring, &isoMsg);//POS Data Code
    }

    if (maxfld < 64) {//primary bitmap

        if(mkey != NULL && strlen(mkey)) {
            (void)DL_ISO8583_MSG_SetField_Str(64,0x0,&isoMsg);

            (void) DL_ISO8583_MSG_Pack(&isoHandler, &isoMsg, buf, &bufSize);

            calculateSHA256Hash(buf, bufSize - 64, chash, mkey);

            (void) DL_ISO8583_MSG_SetField_Str(64, chash, &isoMsg);
        }

    } else {//secondary bitmap

        if(mkey != NULL && strlen(mkey)) {
            (void) DL_ISO8583_MSG_SetField_Str(128, 0x0, &isoMsg);

            (void) DL_ISO8583_MSG_Pack(&isoHandler, &isoMsg, buf, &bufSize);

            calculateSHA256Hash(buf, bufSize - 64, chash, mkey);

            (void) DL_ISO8583_MSG_SetField_Str(128, chash, &isoMsg);
        }
    }

    //(*env)->ReleaseStringUTFChars(env,key, mkey);//clear the data from the memory after using

    memset(buf,0x0,sizeof(buf));

    (void)DL_ISO8583_MSG_Pack(&isoHandler,&isoMsg,&buf[2],&bufSize);

    DL_ISO8583_MSG_Free(&isoMsg);

    buf[0] = (unsigned char) (bufSize >> 8);
    buf[1] = (unsigned char) bufSize;

    dl_bin2hex(buf, pcOutBuffer, bufSize + 2);

    /*jbyteArray data = (*env)->NewByteArray(env, bufSize + 2);
    if (data == NULL) {
        return NULL; //  out of memory error thrown
    }

    jbyte *bytes = (*env)->GetByteArrayElements(env, data, 0);

    for ( int i = 0; i < bufSize + 2; i++ )
    {
        bytes[i] = buf[i];
    }

    (*env)->SetByteArrayRegion(env, data, 0, bufSize + 2, bytes);

    (*env)->ReleaseByteArrayElements(env, data, bytes, 0 );*/

    //char s[] = "Kazeem";

    return (*env)->NewStringUTF(env, pcOutBuffer);
}

JNIEXPORT jstring JNICALL
Java_com_besl_nibss_epms_ISO8583_unpackEPMSISO8583Message( JNIEnv *env, jobject thisObj, jstring iso8583data, jstring key) {

    DL_ISO8583_HANDLER isoHandler;
    DL_ISO8583_MSG isoMsg;
    DL_UINT8 buf[MAX_DATASIZE];
    DL_UINT16 bufSize, j;
    DL_ERR err = kDL_ERR_NONE;
    cJSON *root;
    char *output;
    char chash[65];
    char rhash[65];

    DL_ISO8583_DEFS_1987_GetHandler(&isoHandler);

    /* initialise ISO message */
    DL_ISO8583_MSG_Init(NULL, 0, &isoMsg);

    const char * isofields = (*env)->GetStringUTFChars(env, iso8583data, 0);
    const char * mkey = (*env)->GetStringUTFChars(env, key, 0);

    bufSize = strlen(isofields)/2;

    memset(buf,0,sizeof(buf));
    dl_hex2bin(isofields, buf, bufSize);

    /* unpack ISO message */
    (void)DL_ISO8583_MSG_Unpack(&isoHandler, &buf[2], bufSize - 2, &isoMsg);

    if(mkey != NULL && strlen(mkey)) {
       calculateSHA256Hash(&buf[2], (bufSize - 2)-64, chash, mkey);
    }

    /*if (err != kDL_ERR_NONE) {
        return NULL;
    }*/

    root=cJSON_CreateObject();

    for (j = 0; j < (isoHandler.fieldItems); j++) {

        if (NULL != isoMsg.field[j].ptr) // present
        {

            DL_ISO8583_FIELD_DEF *fieldDef = DL_ISO8583_GetFieldDef(j, &isoHandler);

            if (j == 0) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"0",buf);
            }

            if (j == 2) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"2",buf);
            }

            if (j == 3) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"3",buf);
            }

            if (j == 4) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"4",buf);
            }

            if (j == 5) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"5",buf);
            }

            if (j == 6) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"6",buf);
            }

            if (j == 7) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"7",buf);
            }

            if (j == 8) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"8",buf);
            }

            if (j == 9) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"9",buf);
            }

            if (j == 10) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"10",buf);
            }

            if (j == 11) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"11",buf);
            }

            if (j == 12) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"12",buf);
            }

            if (j == 13) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"13",buf);
            }

            if (j == 14) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"14",buf);
            }

            if (j == 15) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"15",buf);
            }

            if (j == 16) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"16",buf);
            }

            if (j == 17) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"17",buf);
            }

            if (j == 18) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"18",buf);
            }

            if (j == 19) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"19",buf);
            }

            if (j == 20) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"20",buf);
            }

            if (j == 21) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"21",buf);
            }

            if (j == 22) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"22",buf);
            }

            if (j == 23) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"23",buf);
            }

            if (j == 24) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"24",buf);
            }

            if (j == 25) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"25",buf);
            }

            if (j == 26) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"26",buf);
            }

            if (j == 27) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"27",buf);
            }

            if (j == 28) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"28",buf);
            }

            if (j == 29) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"29",buf);
            }

            if (j == 30) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"30",buf);
            }

            if (j == 31) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"31",buf);
            }

            if (j == 32) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"32",buf);
            }

            if (j == 33) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"33",buf);
            }

            if (j == 34) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"34",buf);
            }

            if (j == 35) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"35",buf);
            }

            if (j == 36) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"36",buf);
            }

            if (j == 37) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"37",buf);
            }

            if (j == 38) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"38",buf);
            }

            if (j == 39) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"39",buf);
            }

            if (j == 40) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"40",buf);
            }

            if (j == 41) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"41",buf);
            }

            if (j == 42) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"42",buf);
            }

            if (j == 43) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"43",buf);
            }

            if (j == 44) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"44",buf);
            }

            if (j == 45) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"45",buf);
            }

            if (j == 46) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"46",buf);
            }

            if (j == 47) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"47",buf);
            }

            if (j == 48) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"48",buf);
            }

            if (j == 49) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"49",buf);
            }

            if (j == 50) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"50",buf);
            }

            if (j == 51) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"51",buf);
            }

            if (j == 52) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"52",buf);
            }

            if (j == 53) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"53",buf);
            }

            if (j == 54) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"54",buf);
            }

            if (j == 55) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"55",buf);
            }

            if (j == 56) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"56",buf);
            }

            if (j == 57) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"57",buf);
            }

            if (j == 58) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"58",buf);
            }

            if (j == 59) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"59",buf);
            }

            if (j == 60) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"60",buf);
            }

            if (j == 61) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"61",buf);
            }

            if (j == 62) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"62",buf);
            }

            if (j == 63) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"63",buf);
            }

            if (j == 64) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"64",buf);

                if(mkey != NULL && strlen(mkey)) {
                    //checking hash verification
                    memset(rhash, 0, sizeof(rhash));
                    memcpy(rhash, isoMsg.field[j].ptr, isoMsg.field[j].len);
                    toUpperCase(rhash);
                    toUpperCase(chash);

                    if (memcmp(chash, rhash, strlen(chash))) {
                        //hash failed
                        /* free ISO message */
                        DL_ISO8583_MSG_Free(&isoMsg);

                        output = cJSON_Print(root);
                        cJSON_Delete(root);

                        return NULL;
                    }
                }

            }

            if (j == 65) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"65",buf);
            }

            if (j == 123) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"123",buf);
            }

            if (j == 128) {
                memset(buf, 0, sizeof (buf));
                memcpy(buf, isoMsg.field[j].ptr, isoMsg.field[j].len);
                cJSON_AddStringToObject(root,"128",buf);

                if(mkey != NULL && strlen(mkey)) {
                    //checking hash verification
                    memset(rhash, 0, sizeof(rhash));
                    memcpy(rhash, isoMsg.field[j].ptr, isoMsg.field[j].len);
                    toUpperCase(rhash);
                    toUpperCase(chash);

                    if (memcmp(chash, rhash, strlen(chash))) {
                        //hash failed
                        /* free ISO message */
                        DL_ISO8583_MSG_Free(&isoMsg);

                        output = cJSON_Print(root);
                        cJSON_Delete(root);

                        return NULL;
                    }
                }

            }

        }

    } // end-for(j)

    /* free ISO message */
    DL_ISO8583_MSG_Free(&isoMsg);

    output=cJSON_Print(root);
    cJSON_Delete(root);
    //free(output);

    return (*env)->NewStringUTF(env, output);
    
}
