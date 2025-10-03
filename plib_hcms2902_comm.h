#ifndef PLIB_HCMS2902_COMM_H
#define PLIB_HCMS2902_COMM_H

/**
 * @file plib_hcms2902_comm.h
 * @brief Bibliothèque de communication pour l'afficheur HCMS-2902
 * @author Ramiro Najera
 * @version 1.0.1
 * @date 2025-04-23
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

/**
 * @struct HCMS2902Comm_t
 * @brief Communication série de l'afficheur HCMS2902
 */
typedef struct
{
    /** @brief Délai de transition entre chaque pin */
    unsigned long delay;
    /** @brief Pin Chip Enable */
    GPIO_t pinCE; 
    /** @brief Pin Data In */             
    GPIO_t pinDIN;
    /** @brief Pin Clock */
    GPIO_t pinCLK;
    /** @brief Pin Register Selection */
    GPIO_t pinRS;
}HCMS2902Comm_t;

/**
 * @brief Génère une impulsion d'horloge pour la communication.
 * @param comm Pointeur vers la structure de configuration de la communication.
 */
void HCMS2902_GenerateClock(HCMS2902Comm_t *comm);

/**
 * @brief Initialise la communication avec l'afficheur HCMS-2902.
 * @param comm Pointeur vers la structure de configuration de la communication.
 */
void HCMS2902_GenerateInit(HCMS2902Comm_t *comm);

/**
 * @brief Envoie un octet de données à l'afficheur via la communication.
 * @param comm Pointeur vers la structure de configuration de la communication.
 * @param reg Octet à envoyer.
 */
void HCMS2902_Write(HCMS2902Comm_t *comm, char reg);

/**
 * @brief Envoie plusieurs octets de données à l'afficheur.
 * @param comm Pointeur vers la structure de configuration de la communication.
 * @param a Premier octet.
 * @param b Deuxième octet.
 * @param c Troisième octet.
 * @param d Quatrième octet.
 * @param e Cinquième octet.
 */
void HCMS2902_WriteArray(HCMS2902Comm_t *comm, char a, char b, char c, char d, char e);

/**
 * @brief Écrit une valeur dans le registre 0 de l'afficheur.
 * @param comm Pointeur vers la structure de configuration de la communication.
 * @param reg Valeur à écrire dans le registre 0.
 */
void HCMS2902_WriteREG0(HCMS2902Comm_t *comm, char reg);

/**
 * @brief Ajuste la luminosité de l'afficheur en envoyant une valeur au registre approprié.
 * @param comm Pointeur vers la structure de configuration de la communication.
 * @param val Niveau de luminosité (0-15).
 */
void HCMS2902_WriteBrightness(HCMS2902Comm_t *comm, unsigned char val);

/**
 * @brief Affiche un caractère sur l'afficheur en utilisant la communication.
 * @param comm Pointeur vers la structure de configuration de la communication.
 * @param c Caractère à afficher.
 */
void HCMS2902_WriteChar(HCMS2902Comm_t *comm, char c);

/**
 * @brief Affiche une chaîne de caractères sur l'afficheur HCMS-2902.
 * @param comm Pointeur vers la structure de configuration de la communication.
 * @param text Pointeur vers la chaîne de caractères à afficher.
 */
void HCMS2902_WriteText(HCMS2902Comm_t *comm, char* text);

#endif  // PLIB_HCMS2902_COMM_H