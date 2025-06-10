#!/bin/bash

gcc -o RandomNumgiverSetNewPLaceupfl RandomNumgiverSetNewPLaceupfl.c
gcc -o GUIForShowDateFromRNGSNP GUIForShowDateFromRNGSNP.c
./RandomNumgiverSetNewPLaceupfl output.txt
./GUIForShowDateFromRNGSNP output.txt 