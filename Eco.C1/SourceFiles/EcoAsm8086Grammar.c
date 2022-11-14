/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoAsm8086Grammar
 * </сводка>
 *
 * <описание>
 *   Данный файл реализует описание грамматики
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "EcoAsm8086Grammar.h"

/*
 *
 * <сводка>
 *   Функция GetFAForLAOfAsm8086
 * </сводка>
 *
 * <описание>
 *   Функция GetFAForLAOfAsm8086 - возвращает конечный автомат для лексического анализа ассемблера под 8086 процессор
 * </описание>
 *
 */
IEcoFSM1StateMachine* GetFAForLAOfAsm8086(IEcoFSM1* pIFSM) {
    IEcoFSM1StateMachine* pIFA = 0;
    char_t pszStateName[4] = {0};
    uint32_t index = 0;
    IEcoFSM1Event* pIEvent[256] = {0};
    IEcoFSM1State* pIState[99] = {0};

    /* Создаем конечный автомат */
    pIFA = pIFSM->pVTbl->CreateStateMachine(pIFSM, "ASM8086");
    for (index = 0; index < 99; index++) {
        pszStateName[0] = 'q';
        pszStateName[1] = index/10 + 48;
        pszStateName[2] = index%10 + 48;
        pIState[index] = pIFA->pVTbl->AddState(pIFA, pszStateName);
    }

    /* Создадим массив событий для алфавита по прядку кодов ASCII таблицы */
    /* Конец файла EOF \r\n */
    pIEvent[0] = pIFA->pVTbl->AddEvent(pIFA, "EOF", 0, 0);
    /* Конец строки \r\n */
    pIEvent[10] = pIFA->pVTbl->AddEvent(pIFA, "LF", 10, 0);
    pIEvent[13] = pIFA->pVTbl->AddEvent(pIFA, "CR", 13, 0);
    /* Пробел и табуляция */
    pIEvent[9] = pIFA->pVTbl->AddEvent(pIFA, "HT", 9, 0);
    pIEvent[32] = pIFA->pVTbl->AddEvent(pIFA, "SP", 32, 0);
    /* Пунктуация */
    pIEvent['!'] = pIFA->pVTbl->AddEvent(pIFA, "!", '!', 0);
    pIEvent['"'] = pIFA->pVTbl->AddEvent(pIFA, "\"", '"', 0);
    pIEvent['#'] = pIFA->pVTbl->AddEvent(pIFA, "#", '#', 0);
    pIEvent['$'] = pIFA->pVTbl->AddEvent(pIFA, "$", '$', 0);
    pIEvent['%'] = pIFA->pVTbl->AddEvent(pIFA, "%", '%', 0);
    pIEvent['&'] = pIFA->pVTbl->AddEvent(pIFA, "&", '&', 0);
    pIEvent['\''] = pIFA->pVTbl->AddEvent(pIFA, "'", '\'', 0);
    pIEvent['('] = pIFA->pVTbl->AddEvent(pIFA, "(", '(', 0);
    pIEvent[')'] = pIFA->pVTbl->AddEvent(pIFA, ")", ')', 0);
    pIEvent['*'] = pIFA->pVTbl->AddEvent(pIFA, "*", '*', 0);
    pIEvent['+'] = pIFA->pVTbl->AddEvent(pIFA, "+", '+', 0);
    pIEvent[','] = pIFA->pVTbl->AddEvent(pIFA, ",", ',', 0);
    pIEvent['-'] = pIFA->pVTbl->AddEvent(pIFA, "-", '-', 0);
    pIEvent['.'] = pIFA->pVTbl->AddEvent(pIFA, ".", '.', 0);
    pIEvent['/'] = pIFA->pVTbl->AddEvent(pIFA, "/", '/', 0);
    /* Диапазон [0-9] */
    pIEvent['0'] = pIFA->pVTbl->AddEvent(pIFA, "0", '0', 0);
    pIEvent['1'] = pIFA->pVTbl->AddEvent(pIFA, "1", '1', 0);
    pIEvent['2'] = pIFA->pVTbl->AddEvent(pIFA, "2", '2', 0);
    pIEvent['3'] = pIFA->pVTbl->AddEvent(pIFA, "3", '3', 0);
    pIEvent['4'] = pIFA->pVTbl->AddEvent(pIFA, "4", '4', 0);
    pIEvent['5'] = pIFA->pVTbl->AddEvent(pIFA, "5", '5', 0);
    pIEvent['6'] = pIFA->pVTbl->AddEvent(pIFA, "6", '6', 0);
    pIEvent['7'] = pIFA->pVTbl->AddEvent(pIFA, "7", '7', 0);
    pIEvent['8'] = pIFA->pVTbl->AddEvent(pIFA, "8", '8', 0);
    pIEvent['9'] = pIFA->pVTbl->AddEvent(pIFA, "9", '9', 0);
    /* Пунктуация */
    pIEvent[':'] = pIFA->pVTbl->AddEvent(pIFA, ":", ':', 0);
    pIEvent[';'] = pIFA->pVTbl->AddEvent(pIFA, ";", ';', 0);
    pIEvent['<'] = pIFA->pVTbl->AddEvent(pIFA, "<", '<', 0);
    pIEvent['='] = pIFA->pVTbl->AddEvent(pIFA, "=", '=', 0);
    pIEvent['>'] = pIFA->pVTbl->AddEvent(pIFA, ">", '>', 0);
    pIEvent['?'] = pIFA->pVTbl->AddEvent(pIFA, "?", '?', 0);
    pIEvent['@'] = pIFA->pVTbl->AddEvent(pIFA, "@", '@', 0);
    /* Диапазон [A-Z] */
    pIEvent['A'] = pIFA->pVTbl->AddEvent(pIFA, "A", 'A', 0);
    pIEvent['B'] = pIFA->pVTbl->AddEvent(pIFA, "B", 'B', 0);
    pIEvent['C'] = pIFA->pVTbl->AddEvent(pIFA, "C", 'C', 0);
    pIEvent['D'] = pIFA->pVTbl->AddEvent(pIFA, "D", 'D', 0);
    pIEvent['E'] = pIFA->pVTbl->AddEvent(pIFA, "E", 'E', 0);
    pIEvent['F'] = pIFA->pVTbl->AddEvent(pIFA, "F", 'F', 0);
    pIEvent['G'] = pIFA->pVTbl->AddEvent(pIFA, "G", 'G', 0);
    pIEvent['H'] = pIFA->pVTbl->AddEvent(pIFA, "H", 'H', 0);
    pIEvent['I'] = pIFA->pVTbl->AddEvent(pIFA, "I", 'I', 0);
    pIEvent['J'] = pIFA->pVTbl->AddEvent(pIFA, "J", 'J', 0);
    pIEvent['K'] = pIFA->pVTbl->AddEvent(pIFA, "K", 'K', 0);
    pIEvent['L'] = pIFA->pVTbl->AddEvent(pIFA, "L", 'L', 0);
    pIEvent['M'] = pIFA->pVTbl->AddEvent(pIFA, "M", 'M', 0);
    pIEvent['N'] = pIFA->pVTbl->AddEvent(pIFA, "N", 'N', 0);
    pIEvent['O'] = pIFA->pVTbl->AddEvent(pIFA, "O", 'O', 0);
    pIEvent['P'] = pIFA->pVTbl->AddEvent(pIFA, "P", 'P', 0);
    pIEvent['Q'] = pIFA->pVTbl->AddEvent(pIFA, "Q", 'Q', 0);
    pIEvent['R'] = pIFA->pVTbl->AddEvent(pIFA, "R", 'R', 0);
    pIEvent['S'] = pIFA->pVTbl->AddEvent(pIFA, "S", 'S', 0);
    pIEvent['T'] = pIFA->pVTbl->AddEvent(pIFA, "T", 'T', 0);
    pIEvent['U'] = pIFA->pVTbl->AddEvent(pIFA, "U", 'U', 0);
    pIEvent['V'] = pIFA->pVTbl->AddEvent(pIFA, "V", 'V', 0);
    pIEvent['W'] = pIFA->pVTbl->AddEvent(pIFA, "W", 'W', 0);
    pIEvent['X'] = pIFA->pVTbl->AddEvent(pIFA, "X", 'X', 0);
    pIEvent['Y'] = pIFA->pVTbl->AddEvent(pIFA, "Y", 'Y', 0);
    pIEvent['Z'] = pIFA->pVTbl->AddEvent(pIFA, "Z", 'Z', 0);
    /* Пунктуация */
    pIEvent['['] = pIFA->pVTbl->AddEvent(pIFA, "[", '[', 0);
    pIEvent['\\'] = pIFA->pVTbl->AddEvent(pIFA, "\\", '\\', 0);
    pIEvent[']'] = pIFA->pVTbl->AddEvent(pIFA, "]", ']', 0);
    pIEvent['^'] = pIFA->pVTbl->AddEvent(pIFA, "^", '^', 0);
    pIEvent['_'] = pIFA->pVTbl->AddEvent(pIFA, "_", '_', 0);
    pIEvent['`'] = pIFA->pVTbl->AddEvent(pIFA, "`", '`', 0);
    /* Диапазон [a-z] */
    pIEvent['a'] = pIFA->pVTbl->AddEvent(pIFA, "a", 'a', 0);
    pIEvent['b'] = pIFA->pVTbl->AddEvent(pIFA, "b", 'b', 0);
    pIEvent['c'] = pIFA->pVTbl->AddEvent(pIFA, "c", 'c', 0);
    pIEvent['d'] = pIFA->pVTbl->AddEvent(pIFA, "d", 'd', 0);
    pIEvent['e'] = pIFA->pVTbl->AddEvent(pIFA, "e", 'e', 0);
    pIEvent['f'] = pIFA->pVTbl->AddEvent(pIFA, "f", 'f', 0);
    pIEvent['g'] = pIFA->pVTbl->AddEvent(pIFA, "g", 'g', 0);
    pIEvent['h'] = pIFA->pVTbl->AddEvent(pIFA, "h", 'h', 0);
    pIEvent['i'] = pIFA->pVTbl->AddEvent(pIFA, "i", 'i', 0);
    pIEvent['j'] = pIFA->pVTbl->AddEvent(pIFA, "j", 'j', 0);
    pIEvent['k'] = pIFA->pVTbl->AddEvent(pIFA, "k", 'k', 0);
    pIEvent['l'] = pIFA->pVTbl->AddEvent(pIFA, "l", 'l', 0);
    pIEvent['m'] = pIFA->pVTbl->AddEvent(pIFA, "m", 'm', 0);
    pIEvent['n'] = pIFA->pVTbl->AddEvent(pIFA, "n", 'n', 0);
    pIEvent['o'] = pIFA->pVTbl->AddEvent(pIFA, "o", 'o', 0);
    pIEvent['p'] = pIFA->pVTbl->AddEvent(pIFA, "p", 'p', 0);
    pIEvent['q'] = pIFA->pVTbl->AddEvent(pIFA, "q", 'q', 0);
    pIEvent['r'] = pIFA->pVTbl->AddEvent(pIFA, "r", 'r', 0);
    pIEvent['s'] = pIFA->pVTbl->AddEvent(pIFA, "s", 's', 0);
    pIEvent['t'] = pIFA->pVTbl->AddEvent(pIFA, "t", 't', 0);
    pIEvent['u'] = pIFA->pVTbl->AddEvent(pIFA, "u", 'u', 0);
    pIEvent['v'] = pIFA->pVTbl->AddEvent(pIFA, "v", 'v', 0);
    pIEvent['w'] = pIFA->pVTbl->AddEvent(pIFA, "w", 'w', 0);
    pIEvent['x'] = pIFA->pVTbl->AddEvent(pIFA, "x", 'x', 0);
    pIEvent['y'] = pIFA->pVTbl->AddEvent(pIFA, "y", 'y', 0);
    pIEvent['z'] = pIFA->pVTbl->AddEvent(pIFA, "z", 'z', 0);
    /* Пунктуация */
    pIEvent['{'] = pIFA->pVTbl->AddEvent(pIFA, "{", '{', 0);
    pIEvent['|'] = pIFA->pVTbl->AddEvent(pIFA, "|", '|', 0);
    pIEvent['}'] = pIFA->pVTbl->AddEvent(pIFA, "}", '}', 0);
    pIEvent['~'] = pIFA->pVTbl->AddEvent(pIFA, "~", '~', 0);
    pIEvent['~'] = pIFA->pVTbl->AddEvent(pIFA, "~", '~', 0);

    /* Устанавливаем начальное состояние автомата */
    pIState[2]->pVTbl->set_Initial(pIState[2], 1);

    /* Устанавливаем акцепторы - токены */
    pIState[6]->pVTbl->set_Final(pIState[6], 1);
    pIState[6]->pVTbl->set_Parameter(pIState[6], "instructionName");
    pIState[76]->pVTbl->set_Final(pIState[76], 1);
    pIState[76]->pVTbl->set_Parameter(pIState[76], "byteRegister");
    pIState[63]->pVTbl->set_Final(pIState[63], 1);
    pIState[63]->pVTbl->set_Parameter(pIState[63], "wordRegister");
    pIState[82]->pVTbl->set_Final(pIState[82], 1);
    pIState[82]->pVTbl->set_Parameter(pIState[82], "segmentRegister");
    pIState[84]->pVTbl->set_Final(pIState[84], 1);
    pIState[84]->pVTbl->set_Parameter(pIState[84], "dataDefinition");
    pIState[87]->pVTbl->set_Final(pIState[87], 1);
    pIState[87]->pVTbl->set_Parameter(pIState[87], "offsetDirective");
    pIState[89]->pVTbl->set_Final(pIState[89], 1);
    pIState[89]->pVTbl->set_Parameter(pIState[89], "typeDirective");
    pIState[91]->pVTbl->set_Final(pIState[91], 1);
    pIState[91]->pVTbl->set_Parameter(pIState[91], "whitespace");
    pIState[94]->pVTbl->set_Final(pIState[94], 1);
    pIState[94]->pVTbl->set_Parameter(pIState[94], "newline");
    pIState[96]->pVTbl->set_Final(pIState[96], 1);
    pIState[96]->pVTbl->set_Parameter(pIState[96], "comment");
    pIState[98]->pVTbl->set_Final(pIState[98], 1);
    pIState[98]->pVTbl->set_Parameter(pIState[98], "punctuation");

    /* Общая схема переходов нарисована в VISIO */

    /* Создаем переходы для пробелов и табуляции */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[2],  pIState[90]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[2],  pIState[90]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[90],  pIState[90]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[90],  pIState[90]);
    for (index = '!'; index < '~'; index++) {
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[90],  pIState[91]);
    }
    /* Создаем переходы для новой строки */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[2],  pIState[92]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[2],  pIState[93]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[92],  pIState[93]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[93],  pIState[94]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[93],  pIState[94]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[0],  pIState[93],  pIState[94]);
    for (index = ' '; index < '~'; index++) {
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[93],  pIState[94]);
    }

    /* Создаем переходы для пунктуации */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[','],  pIState[2],  pIState[97]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[97],  pIState[98]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[97],  pIState[98]);
    for (index = ' '; index < '~'; index++) {
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[97],  pIState[98]);
    }

    /* Создаем переходы для комментариев */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[';'],  pIState[2],  pIState[95]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[95],  pIState[96]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[95],  pIState[96]);
    for (index = ' '; index < '~'; index++) {
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[95],  pIState[95]);
    }

    /* Создаем переходы для директив */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[2],  pIState[88]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[88],  pIState[89]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[88],  pIState[89]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[88],  pIState[89]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[88],  pIState[89]);
    for (index = '0'; index < '9'; index++) {
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[88],  pIState[88]);
    }
    for (index = 'A'; index < 'Z'; index++) {
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[88],  pIState[88]);
    }
    for (index = 'a'; index < 'z'; index++) {
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[88],  pIState[88]);
    }

    /* Создаем переходы для байтовых регистров общего назначения AH AL BH BL CH CL DH DL */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[2],  pIState[3]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[2],  pIState[3]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['b'],  pIState[2],  pIState[77]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['B'],  pIState[2],  pIState[77]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[3],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[3],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[77],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[77],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[3],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['H'],  pIState[3],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[77],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['H'],  pIState[77],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[2],  pIState[11]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['C'],  pIState[2],  pIState[11]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[11],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[11],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[11],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['H'],  pIState[11],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[2],  pIState[18]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['D'],  pIState[2],  pIState[18]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[18],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[18],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[18],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['H'],  pIState[18],  pIState[75]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[','],  pIState[75],  pIState[76]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[75],  pIState[76]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[75],  pIState[76]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[75],  pIState[76]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[75],  pIState[76]);
    /* Создаем переходы для двух-байтовых регистров общего назначения AX BX CX DX SP BP SI DI */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['x'],  pIState[3],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['X'],  pIState[3],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['x'],  pIState[77],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['X'],  pIState[77],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[77],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['P'],  pIState[77],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['x'],  pIState[11],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['X'],  pIState[11],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['x'],  pIState[18],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['X'],  pIState[18],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[18],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['I'],  pIState[18],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[60],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['P'],  pIState[60],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[60],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['I'],  pIState[60],  pIState[74]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[','],  pIState[74],  pIState[63]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[74],  pIState[63]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[74],  pIState[63]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[74],  pIState[63]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[74],  pIState[63]);
    /* Создаем переходы для сегментных-регистров CS DS SS ES */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[60],  pIState[81]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[60],  pIState[81]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[11],  pIState[81]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[11],  pIState[81]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[18],  pIState[81]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[18],  pIState[81]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[20],  pIState[82]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[20],  pIState[82]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[81],  pIState[82]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[81],  pIState[82]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[','],  pIState[81],  pIState[82]);
    /* Создаем переходы для определения данных DD DW DB */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['b'],  pIState[18],  pIState[83]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['B'],  pIState[18],  pIState[83]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['w'],  pIState[18],  pIState[83]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['W'],  pIState[18],  pIState[83]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[18],  pIState[83]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['D'],  pIState[18],  pIState[83]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[83],  pIState[84]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[83],  pIState[84]);
    /* Создаем переходы для мнемоники AAA AAD AAM AAS */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[3],  pIState[4]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[3],  pIState[4]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[4],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[4],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[4],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['D'],  pIState[4],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['m'],  pIState[4],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['M'],  pIState[4],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[4],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[4],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[5],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[5],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[','],  pIState[5],  pIState[6]);
    /* Создаем переходы для мнемоники ADD ADC */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[3],  pIState[9]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['D'],  pIState[3],  pIState[9]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[9],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['D'],  pIState[9],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[9],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['C'],  pIState[9],  pIState[5]);
    /* Создаем переходы для мнемоники CALL */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[11],  pIState[12]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[11],  pIState[12]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[12],  pIState[13]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[12],  pIState[13]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[13],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[13],  pIState[5]);
    /* Создаем переходы для мнемоники CBW */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['b'],  pIState[11],  pIState[14]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['B'],  pIState[11],  pIState[14]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['w'],  pIState[14],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['W'],  pIState[14],  pIState[5]);
    /* Создаем переходы для мнемоники CLC CLD CLI */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[11],  pIState[15]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[11],  pIState[15]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[15],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['C'],  pIState[15],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[15],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['D'],  pIState[15],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[15],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['I'],  pIState[15],  pIState[5]);
    /* Создаем переходы для мнемоники CMC CMP CMPS */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['m'],  pIState[11],  pIState[16]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['M'],  pIState[11],  pIState[16]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[16],  pIState[17]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['P'],  pIState[16],  pIState[17]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[17],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[17],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[17],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[17],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[16],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['C'],  pIState[16],  pIState[5]);
    /* Создаем переходы для мнемоники CWD */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['w'],  pIState[11],  pIState[10]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['W'],  pIState[11],  pIState[10]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[10],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['D'],  pIState[10],  pIState[5]);
    /* Создаем переходы для мнемоники DAA DAS DEC DIV */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[18],  pIState[19]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[18],  pIState[19]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[19],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[19],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[19],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[19],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[18],  pIState[20]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[18],  pIState[20]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[20],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['C'],  pIState[20],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[18],  pIState[21]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['I'],  pIState[18],  pIState[21]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['v'],  pIState[21],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['V'],  pIState[21],  pIState[5]);
    /* Создаем переходы для мнемоники ESC */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[2],  pIState[22]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[2],  pIState[22]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[22],  pIState[20]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[22],  pIState[20]);
    /* Создаем переходы для мнемоники HLT */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[2],  pIState[23]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['H'],  pIState[2],  pIState[23]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[23],  pIState[24]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[23],  pIState[24]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[24],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['T'],  pIState[24],  pIState[5]);
    /* Создаем переходы для мнемоники IDIV */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[2],  pIState[25]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['I'],  pIState[2],  pIState[25]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[25],  pIState[26]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['D'],  pIState[25],  pIState[26]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[26],  pIState[21]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['I'],  pIState[26],  pIState[21]);
    /* Создаем переходы для мнемоники IMUL */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['m'],  pIState[25],  pIState[27]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['M'],  pIState[25],  pIState[27]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[27],  pIState[13]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['U'],  pIState[27],  pIState[13]);
    /* Создаем переходы для мнемоники IN */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[25],  pIState[28]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['N'],  pIState[25],  pIState[28]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[28],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[28],  pIState[6]);
    /* Создаем переходы для мнемоники INC INT INTO */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[28],  pIState[29]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['T'],  pIState[28],  pIState[29]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[29],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[29],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[29],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[29],  pIState[6]);
    /* Создаем переходы для мнемоники IRET */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[28],  pIState[30]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['R'],  pIState[28],  pIState[30]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[30],  pIState[24]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[30],  pIState[24]);
    /* Создаем переходы для мнемоники JA JAE JB JBE JG JGE JL JLE*/
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['j'],  pIState[2],  pIState[31]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['J'],  pIState[2],  pIState[31]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[31],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[31],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['b'],  pIState[31],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['B'],  pIState[31],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['g'],  pIState[31],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['G'],  pIState[31],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[31],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[31],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[32],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[32],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[32],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[32],  pIState[5]);
    /* Создаем переходы для мнемоники JE JO JS JZ */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[31],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[31],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[31],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[31],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[31],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[31],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['z'],  pIState[31],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['Z'],  pIState[31],  pIState[5]);
    /* Создаем переходы для мнемоники JCXZ */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[31],  pIState[33]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['C'],  pIState[31],  pIState[33]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['x'],  pIState[33],  pIState[34]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['X'],  pIState[33],  pIState[34]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['z'],  pIState[34],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['Z'],  pIState[34],  pIState[5]);
    /* Создаем переходы для мнемоники JMP */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['m'],  pIState[31],  pIState[35]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['M'],  pIState[31],  pIState[35]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[35],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['P'],  pIState[35],  pIState[5]);
    /* Создаем переходы для мнемоники JNA JNAE JNB JNBE JNG JNGE JNL JNLE */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[31],  pIState[36]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['N'],  pIState[31],  pIState[36]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[36],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[36],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['b'],  pIState[36],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['B'],  pIState[36],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['g'],  pIState[36],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['G'],  pIState[36],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[36],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[36],  pIState[32]);
    /* Создаем переходы для мнемоники JNE */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[36],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[36],  pIState[5]);
    /* Создаем переходы для мнемоники JP JPE JPO */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[31],  pIState[37]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['P'],  pIState[31],  pIState[37]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[37],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[37],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[37],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[37],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[37],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[37],  pIState[5]);
    /* Создаем переходы для мнемоники JNO JNP JNS JNZ */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[36],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[36],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[36],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['P'],  pIState[36],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[36],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[36],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['z'],  pIState[36],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['Z'],  pIState[36],  pIState[5]);
    /* Создаем переходы для мнемоники LAHF */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[2],  pIState[38]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[2],  pIState[38]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[38],  pIState[39]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[38],  pIState[39]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[39],  pIState[41]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['H'],  pIState[39],  pIState[41]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['f'],  pIState[41],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['F'],  pIState[41],  pIState[5]);
    /* Создаем переходы для мнемоники LDS */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[38],  pIState[17]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['D'],  pIState[38],  pIState[17]);
    /* Создаем переходы для мнемоники LEA LES */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[38],  pIState[19]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[38],  pIState[19]);
    /* Создаем переходы для мнемоники LOCK */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[38],  pIState[40]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[38],  pIState[40]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[40],  pIState[45]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['C'],  pIState[40],  pIState[45]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['k'],  pIState[45],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['K'],  pIState[45],  pIState[5]);
    /* Создаем переходы для мнемоники LODS */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[40],  pIState[17]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['D'],  pIState[40],  pIState[17]);
    /* Создаем переходы для мнемоники LOOP LOOPE LOOPNE LOOPNZ LOOPZ */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[40],  pIState[42]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[40],  pIState[42]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[42],  pIState[43]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['P'],  pIState[42],  pIState[43]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[43],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[43],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[43],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[43],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['z'],  pIState[43],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['Z'],  pIState[43],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[43],  pIState[44]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['N'],  pIState[43],  pIState[44]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[44],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[44],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['z'],  pIState[44],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['Z'],  pIState[44],  pIState[5]);
    /* Создаем переходы для мнемоники MOV MOVS */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['m'],  pIState[2],  pIState[46]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['M'],  pIState[2],  pIState[46]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[46],  pIState[78]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[46],  pIState[78]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['v'],  pIState[78],  pIState[48]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['V'],  pIState[78],  pIState[48]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[48],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[48],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[48],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[48],  pIState[5]);
    /* Создаем переходы для мнемоники MUL */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[46],  pIState[47]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['U'],  pIState[46],  pIState[47]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[47],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[47],  pIState[5]);
    /* Создаем переходы для мнемоники NEG */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[2],  pIState[49]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['N'],  pIState[2],  pIState[49]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[49],  pIState[79]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[49],  pIState[79]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['g'],  pIState[79],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['G'],  pIState[79],  pIState[5]);
    /* Создаем переходы для мнемоники NOP NOT */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[49],  pIState[50]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[49],  pIState[50]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[50],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['P'],  pIState[50],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[50],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['T'],  pIState[50],  pIState[5]);
    /* Создаем переходы для мнемоники OR */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[2],  pIState[51]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[2],  pIState[51]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[51],  pIState[85]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['R'],  pIState[51],  pIState[85]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[85],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[85],  pIState[6]);
    /* Создаем переходы для мнемоники OUT */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[51],  pIState[24]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['U'],  pIState[51],  pIState[24]);
    /* Создаем переходы для мнемоники POP POPF */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[2],  pIState[52]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['P'],  pIState[2],  pIState[52]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[52],  pIState[53]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[52],  pIState[53]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[53],  pIState[54]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['P'],  pIState[53],  pIState[54]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[54],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[54],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['f'],  pIState[54],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['F'],  pIState[54],  pIState[5]);
    /* Создаем переходы для мнемоники PUSH PUSHF */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[52],  pIState[55]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['U'],  pIState[52],  pIState[55]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[55],  pIState[56]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[55],  pIState[56]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[56],  pIState[57]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['H'],  pIState[56],  pIState[57]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[57],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[57],  pIState[6]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['f'],  pIState[57],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['F'],  pIState[57],  pIState[5]);
    /* Создаем переходы для мнемоники RCL RCR ROR ROL */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[2],  pIState[58]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['R'],  pIState[2],  pIState[58]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[58],  pIState[59]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['C'],  pIState[58],  pIState[59]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[58],  pIState[59]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[58],  pIState[59]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[59],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[59],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[59],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['R'],  pIState[59],  pIState[5]);
    /* Создаем переходы для мнемоники REP RET */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[58],  pIState[80]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[58],  pIState[80]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[80],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['P'],  pIState[80],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[80],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['T'],  pIState[80],  pIState[5]);
    /* Создаем переходы для мнемоники SAHF SAL SAR SHL SHR */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[2],  pIState[60]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[2],  pIState[60]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[60],  pIState[61]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[60],  pIState[61]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[61],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[61],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[61],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['R'],  pIState[61],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[61],  pIState[41]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['H'],  pIState[61],  pIState[41]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[60],  pIState[59]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['H'],  pIState[60],  pIState[59]);
    /* Создаем переходы для мнемоники SBB SUB */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['b'],  pIState[60],  pIState[65]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['B'],  pIState[60],  pIState[65]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[60],  pIState[65]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['U'],  pIState[60],  pIState[65]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['b'],  pIState[65],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['B'],  pIState[65],  pIState[5]);
    /* Создаем переходы для мнемоники SCAS */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[60],  pIState[62]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['C'],  pIState[60],  pIState[62]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[62],  pIState[17]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[62],  pIState[17]);
    /* Создаем переходы для мнемоники STOS */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[60],  pIState[64]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['T'],  pIState[60],  pIState[64]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[64],  pIState[17]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[64],  pIState[17]);
    /* Создаем переходы для мнемоники STC STD STI */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[64],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['C'],  pIState[64],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[64],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['D'],  pIState[64],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[64],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['I'],  pIState[64],  pIState[5]);
    /* Создаем переходы для мнемоники TEST */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[2],  pIState[66]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['T'],  pIState[2],  pIState[66]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[66],  pIState[67]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[66],  pIState[67]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[67],  pIState[24]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['S'],  pIState[67],  pIState[24]);
    /* Создаем переходы для мнемоники WAIT */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['w'],  pIState[2],  pIState[68]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['W'],  pIState[2],  pIState[68]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[68],  pIState[69]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[68],  pIState[69]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[69],  pIState[24]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['I'],  pIState[69],  pIState[24]);
    /* Создаем переходы для мнемоники XCHG */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['x'],  pIState[2],  pIState[70]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['X'],  pIState[2],  pIState[70]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[70],  pIState[71]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['C'],  pIState[70],  pIState[71]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[71],  pIState[79]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['H'],  pIState[71],  pIState[79]);
    /* Создаем переходы для мнемоники XLAT */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[70],  pIState[72]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[70],  pIState[72]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[72],  pIState[24]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['A'],  pIState[72],  pIState[24]);
    /* Создаем переходы для мнемоники XOR */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[70],  pIState[73]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['O'],  pIState[70],  pIState[73]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[73],  pIState[5]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['R'],  pIState[73],  pIState[5]);

    /* Создаем переходы для директив счетчика (смещение) ORG */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['g'],  pIState[85],  pIState[86]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['G'],  pIState[85],  pIState[86]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[86],  pIState[87]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[86],  pIState[87]);

    /* Создаем переходы для директив */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[2],  pIState[88]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[88],  pIState[89]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[88],  pIState[89]);

    return pIFA;
}
