#include "funzioni.h"

void initializeColorSprite() {
    // Definizione colori
    init_color(FROG_LIGHT_GREEN1, 710, 830, 635);    // Light Green 1
    init_color(FROG_LIGHT_GREEN2, 555, 850, 450);    // Light Green 2
    init_color(FROG_MEDIUM_GREEN1, 278, 827, 349);   // Medium Green 1
    init_color(FROG_MEDIUM_GREEN2, 129, 450, 274);   // Medium Green 2
    init_color(FROG_DARK_GREEN, 235, 490, 133);      // Dark Green 1
    init_color(FROG_DARK_GREEN2, 70, 310, 100);      // Dark Green 2
    init_color(FROG_YELLOW, 1000, 1000, 0);          // Yellow

    // Associa colori a coppie foreground/background
    init_pair(9, COLOR_BLACK, FROG_LIGHT_GREEN1);    // Coppia per 9
    init_pair(10, COLOR_BLACK, FROG_LIGHT_GREEN2);   // Coppia per 10
    init_pair(11, COLOR_BLACK, FROG_MEDIUM_GREEN1);  // Coppia per 11
    init_pair(12, COLOR_BLACK, FROG_MEDIUM_GREEN2);  // Coppia per 12
    init_pair(13, COLOR_BLACK, FROG_DARK_GREEN);     // Coppia per 13
    init_pair(14, COLOR_BLACK, FROG_YELLOW);         // Coppia per 14
}
