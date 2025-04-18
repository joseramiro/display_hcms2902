#ifndef PLIB_HCMS2902_H
#define PLIB_HCMS2902_H

/**
 * @file plib_hcms2901.c
 * @brief Bibliothèque de l'afficheur HCMS-2902
 * @author Ramiro Najera
 * @version 1.0
 * @date 2025-03-18
 * @copyright Copyright (c) 2025
 */

#include "plib_hcms2902_comm.h"

/** @brief Valeur maximale de luminosité de l'afficheur */
#define HCMS2902_LIGHT_MAX    15
/** @brief Valeur minimale de luminosité de l'afficheur */
#define HCMS2902_LIGHT_MIN    0
 
/**
 * @brief Structure de configuration pour l'afficheur HCMS-2902.
 */
typedef struct
{
    unsigned char id;         /**< Identifiant de l'afficheur */
    unsigned char brightness; /**< Niveau de luminosité (0-15) */
    DisplayCommConf comm;     /**< Configuration de la communication */
}HCMS2902Conf_t;

/**
 * @brief Initialise l'afficheur HCMS-2902 avec la configuration spécifiée.
 * @param conf Pointeur vers la structure de configuration de l'afficheur.
 */
void HCMS2902_Init(HCMS2902Conf_t *conf);

/**
 * @brief Met à jour la luminosité de l'afficheur HCMS-2902.
 * @param conf Pointeur vers la structure de configuration de l'afficheur.
 * @param val Nouvelle valeur de luminosité (0-15).
 */
void HCMS2902_UpdateBrightness(HCMS2902Conf_t *conf, unsigned char val);

/**
 * @brief Met à jour le texte affiché sur l'afficheur HCMS-2902.
 * @param conf Pointeur vers la structure de configuration de l'afficheur.
 * @param text Pointeur vers la chaîne de caractères à afficher.
 */
void HCMS2902_UpdateText(HCMS2902Conf_t *conf, char* text);

#endif  // PLIB_HCMS2902_H