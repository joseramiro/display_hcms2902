#ifndef PLIB_HCMS2902_COMM_H
#define PLIB_HCMS2902_COMM_H

/**
 * @file plib_hcms2902_comm.h
 * @brief Bibliothèque de communication pour l'afficheur HCMS-2902
 * @author Ramiro Najera
 * @version 1.0
 * @date 2025-03-18
 * @copyright Copyright (c) 2025
 */

#include "libs/common_c_libs/plib_delay.h"
#include "libs/common_c_libs/plib_comm_struct.h"

/** @brief Nombre de chiffres dans display */
#define HCMS2902_NUM_DIGITS             4
/** @brief Nombre de points dans une colomne */
#define HCMS2902_NUM_DOTS_IN_COLUMN     8
/** @brief Nombre de columnes d'anodes par chiffre */
#define HCMS2902_NUM_COLUMNS            5
/** @brief Masque pour le bit du poinds plus lourd */
#define HCMS2901_MSB_MASK               0x80
/** @brief Masque pour configuration de la luminosité */
#define HCMS2901_BRIGHTNESS_MASK        0x40

typedef struct
{
    unsigned long delay;    /**< Délai entre chaque transition de pins */
    GPIOPin_t ce;
    GPIOPin_t din;
    GPIOPin_t clk;
    GPIOPin_t rs;
}DisplayCommConf;

/**
 * @brief Génère une impulsion d'horloge pour la communication.
 * @param comm Pointeur vers la structure de configuration de la communication.
 */
void HCMS2902_GenerateClock(DisplayCommConf *comm);

/**
 * @brief Initialise la communication avec l'afficheur HCMS-2902.
 * @param comm Pointeur vers la structure de configuration de la communication.
 */
void HCMS2902_GenerateInit(DisplayCommConf *comm);

/**
 * @brief Envoie un octet de données à l'afficheur via la communication.
 * @param comm Pointeur vers la structure de configuration de la communication.
 * @param reg Octet à envoyer.
 */
void HCMS2902_Write(DisplayCommConf *comm, char reg);

/**
 * @brief Envoie plusieurs octets de données à l'afficheur.
 * @param comm Pointeur vers la structure de configuration de la communication.
 * @param a Premier octet.
 * @param b Deuxième octet.
 * @param c Troisième octet.
 * @param d Quatrième octet.
 * @param e Cinquième octet.
 */
void HCMS2902_WriteArray(DisplayCommConf *comm, char a, char b, char c, char d, char e);

/**
 * @brief Écrit une valeur dans le registre 0 de l'afficheur.
 * @param comm Pointeur vers la structure de configuration de la communication.
 * @param reg Valeur à écrire dans le registre 0.
 */
void HCMS2902_WriteREG0(DisplayCommConf *comm, char reg);

/**
 * @brief Ajuste la luminosité de l'afficheur en envoyant une valeur au registre approprié.
 * @param comm Pointeur vers la structure de configuration de la communication.
 * @param val Niveau de luminosité (0-15).
 */
void HCMS2902_WriteBrightness(DisplayCommConf *comm, unsigned char val);

/**
 * @brief Affiche un caractère sur l'afficheur en utilisant la communication.
 * @param comm Pointeur vers la structure de configuration de la communication.
 * @param c Caractère à afficher.
 */
void HCMS2902_WriteChar(DisplayCommConf *comm, char c);

/**
 * @brief Affiche une chaîne de caractères sur l'afficheur HCMS-2902.
 * @param comm Pointeur vers la structure de configuration de la communication.
 * @param text Pointeur vers la chaîne de caractères à afficher.
 */
void HCMS2902_WriteText(DisplayCommConf *comm, char* text);


#endif  // PLIB_HCMS2902_COMM_H