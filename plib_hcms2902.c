/**
 * @file plib_hcms2901.c
 * @brief Bibliothèque de l'afficheur HCMS-2902
 * @author Ramiro Najera
 * @version 1.0
 * @date 2025-03-18
 * @copyright Copyright (c) 2025
 */

#include "plib_hcms2902.h"
#include "plib_hcms2902_comm.h"

void HCMS2902_Init(HCMS2902Conf_t *conf)
{
    // Generate init sequence
    HCMS2902_GenerateInit(&conf->comm);
    // Set empty text
    HCMS2902_WriteText(&conf->comm, "    ");
    // Set brightness
    HCMS2902_WriteBrightness(&conf->comm, conf->brightness);
}

void HCMS2902_UpdateBrightness(HCMS2902Conf_t *conf, unsigned char val)
{
    // Check limits for v
    if (val < HCMS2902_LIGHT_MIN)
            val = HCMS2902_LIGHT_MIN;
    if (val > HCMS2902_LIGHT_MAX)
            val = HCMS2902_LIGHT_MAX;
    // Update brightness
    HCMS2902_WriteBrightness(&conf->comm, val);
}

void HCMS2902_UpdateText(HCMS2902Conf_t *conf, char* text)
{
    HCMS2902_WriteText(&conf->comm, text);
}