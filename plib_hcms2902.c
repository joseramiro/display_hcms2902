/**
 * @file plib_hcms2902.c
 * @brief Bibliothèque de l'afficheur HCMS-2902
 * @author Ramiro Najera
 * @version 1.0.0
 * @date 2025-04-23
 * @copyright Copyright (c) 2025
 */

#include "plib_hcms2902.h"
#include "plib_hcms2902_comm.h"

void HCMS2902_Init(HCMS2902_t *obj)
{
    // Generate init sequence
    HCMS2902_GenerateInit(&obj->comm);
    // Set empty text
    HCMS2902_WriteText(&obj->comm, "    ");
    // Set brightness
    HCMS2902_WriteBrightness(&obj->comm, obj->brightness);
}

void HCMS2902_UpdateBrightness(HCMS2902_t *obj, unsigned char val)
{
    // Check limits for v
    if (val < HCMS2902_LIGHT_MIN)
            val = HCMS2902_LIGHT_MIN;
    if (val > HCMS2902_LIGHT_MAX)
            val = HCMS2902_LIGHT_MAX;
    // Update brightness
    HCMS2902_WriteBrightness(&obj->comm, val);
}

void HCMS2902_UpdateText(HCMS2902_t *obj, char* text)
{
    HCMS2902_WriteText(&obj->comm, text);
}