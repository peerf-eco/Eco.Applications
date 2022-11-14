/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoC89Grammar
 * </сводка>
 *
 * <описание>
 *   Данный файл является описание грамматики
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "EcoC89Grammar.h"

bool_t MakeTransitions(/* in */ IEcoFSM1State* pISourceState, /* in */ IEcoFSM1State* pITargetState, /* in */ IEcoList1* pIEvents);
bool_t MakeExceptEventTransitions(/* in */ IEcoFSM1State* pISourceState, /* in */ IEcoFSM1State* pITargetState, /* in */ IEcoList1* pIExceptEvents);


/*
 *
 * <сводка>
 *   Функция GetFAForLAOfC89
 * </сводка>
 *
 * <описание>
 *   Функция GetFAForLAOfC89 - возвращает конечный автомат для лексического анализа C89
 * </описание>
 *
 */
IEcoFSM1StateMachine* GetFAForLAOfC89(IEcoFSM1* pIFSM) {
     IEcoFSM1StateMachine* pIFA = 0;
    char_t pszStateName[5] = {0};
    uint32_t index = 0;
    uint32_t y = 0;
    IEcoFSM1Event* pIEvent[256] = {0};
    IEcoFSM1State* pIState[180] = {0};
    char_t pszPunctuators[27] = { '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '{', '|', '}', '~', 127};
    /* Создаем конечный автомат */
    pIFA = pIFSM->pVTbl->CreateStateMachine(pIFSM, "C89");
    for (index = 0; index < 180; index++) {
        pszStateName[0] = 'q';
        pszStateName[1] = index/100 + 48;
        if (index >= 100) {
            pszStateName[2] = (index- 100)/10 + 48;
        }
        else {
            pszStateName[2] = index/10 + 48;
        }
        pszStateName[3] = index%10 + 48;
        pIState[index] = pIFA->pVTbl->AddState(pIFA, pszStateName);
    }

    /* Создадим массив событий для алфавита по прядку кодов ASCII таблицы */
    /* Конец файла EOF */
    pIEvent[0] = pIFA->pVTbl->AddEvent(pIFA, "EOF", 0, 0);
    /* Конец строки \r\n */
    pIEvent[10] = pIFA->pVTbl->AddEvent(pIFA, "LF", 10, 0); /* \n */
    pIEvent[13] = pIFA->pVTbl->AddEvent(pIFA, "CR", 13, 0); /* \r */
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
    pIState[0]->pVTbl->set_Initial(pIState[0], 1);

    /* Устанавливаем акцепторы - токены */
    pIState[143]->pVTbl->set_Final(pIState[143], 1);
    pIState[143]->pVTbl->set_Parameter(pIState[143], "constant");
    pIState[144]->pVTbl->set_Final(pIState[144], 1);
    pIState[144]->pVTbl->set_Parameter(pIState[144], "identifier");
    pIState[145]->pVTbl->set_Final(pIState[145], 1);
    pIState[145]->pVTbl->set_Parameter(pIState[145], "keyword");
    pIState[146]->pVTbl->set_Final(pIState[146], 1);
    pIState[146]->pVTbl->set_Parameter(pIState[146], "string-literal");
    pIState[147]->pVTbl->set_Final(pIState[147], 1);
    pIState[147]->pVTbl->set_Parameter(pIState[147], "comment");
    pIState[148]->pVTbl->set_Final(pIState[148], 1);
    pIState[148]->pVTbl->set_Parameter(pIState[148], "new-line");
    pIState[149]->pVTbl->set_Final(pIState[149], 1);
    pIState[149]->pVTbl->set_Parameter(pIState[149], "white-space");
    pIState[150]->pVTbl->set_Final(pIState[150], 1);
    pIState[150]->pVTbl->set_Parameter(pIState[150], "backslash");
    pIState[151]->pVTbl->set_Final(pIState[151], 1);
    pIState[151]->pVTbl->set_Parameter(pIState[151], "punctuattor");
    pIState[158]->pVTbl->set_Final(pIState[162], 1);
    pIState[158]->pVTbl->set_Parameter(pIState[162], "header-name");
    pIState[158]->pVTbl->set_Final(pIState[160], 1);
    pIState[158]->pVTbl->set_Parameter(pIState[160], "directive");
    /* ловушки - ошибки */
    pIState[158]->pVTbl->set_Trap(pIState[157], 1);
    pIState[158]->pVTbl->set_Parameter(pIState[157], "string-literal not closed");

    pIState[163]->pVTbl->set_Final(pIState[163], 1);
    pIState[163]->pVTbl->set_Parameter(pIState[163], "integer-constant");
    pIState[164]->pVTbl->set_Final(pIState[164], 1);
    pIState[164]->pVTbl->set_Parameter(pIState[164], "floating-constant");
    pIState[165]->pVTbl->set_Final(pIState[165], 1);
    pIState[165]->pVTbl->set_Parameter(pIState[165], "enumeration-constant");
    pIState[166]->pVTbl->set_Final(pIState[166], 1);
    pIState[166]->pVTbl->set_Parameter(pIState[166], "character-constant");

    /* Общая схема переходов нарисована в VISIO */

    /* Создаем переходы для новой строки */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[0],  pIState[1]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[0],  pIState[36]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[1],  pIState[36]);
    for (index = 0; index <= 255; index++) {
        if (index == 10) {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[36],  pIState[148]);
            continue;
        }
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[1],  pIState[148]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[36],  pIState[148]);
    }

    //for (index = ' '; index <= '~'; index++) {                                             // ?  (0 \- 9 a \- z A \- Z \t \sp \r \n)
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[36],  pIState[148]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[155],  pIState[147]);
    //}
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[152],  pIState[152]);           // ?
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[152],  pIState[152]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[152],  pIState[152]);
    //for (index = ' '; index <= '~'; index++) {
    //    if (index == '*') {
    //        continue;
    //    }
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[152],  pIState[152]);
    //}
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[154],  pIState[152]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[154],  pIState[152]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[154],  pIState[152]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[155],  pIState[147]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[155],  pIState[147]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[155],  pIState[147]);
    //for (index = ' '; index <= '~'; index++) {
    //    if (index == '/') {
    //        continue;
    //    }
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[154],  pIState[152]);
    //}

    /* Создаем переходы для пробелов и табуляции */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[0],  pIState[2]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[0],  pIState[2]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[2],  pIState[2]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[2],  pIState[2]);
    for (index = 0; index <= 255; index++) {
        if (index == 9 || index == 32) {
            continue;
        }
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[2],  pIState[149]);
    }

    /* Создаем переходы для пунктуатора и комментария */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['/'],  pIState[0],  pIState[28]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['*'],  pIState[28],  pIState[152]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['*'],  pIState[152],  pIState[154]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['/'],  pIState[154],  pIState[155]);
    for (index = 0; index <= 255; index++) {
        if (index == '*') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[154],  pIState[154]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[155],  pIState[147]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[28],  pIState[151]);
            continue;
        }
        if (index == '/') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[152],  pIState[152]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[155],  pIState[147]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[28],  pIState[151]);
            continue;
        }
        if (index == '>') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[28],  pIState[126]);
            continue;
        }
        if (index == '=') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[28],  pIState[126]);
            continue;
        }
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[152],  pIState[152]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[154],  pIState[152]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[155],  pIState[147]);
        /* пунктуатор */
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[28],  pIState[151]);
    }

    /* Пунктуатор */
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[0],  pIState[22]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['-'],  pIState[0],  pIState[23]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['-'],  pIState[23],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['+'],  pIState[0],  pIState[24]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['+'],  pIState[24],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['&'],  pIState[0],  pIState[25]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['&'],  pIState[25],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['*'],  pIState[0],  pIState[26]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['*'],  pIState[23],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['!'],  pIState[0],  pIState[26]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['^'],  pIState[0],  pIState[26]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['|'],  pIState[0],  pIState[27]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['|'],  pIState[26],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['|'],  pIState[27],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['%'],  pIState[0],  pIState[29]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['%'],  pIState[30],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['%'],  pIState[43],  pIState[66]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['<'],  pIState[0],  pIState[30]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['<'],  pIState[30],  pIState[44]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['<'],  pIState[44],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[0],  pIState[31]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[23],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[28],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[29],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[31],  pIState[44]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[0],  pIState[32]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[23],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[24],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[25],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[26],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[27],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[28],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[29],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[30],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[31],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[32],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[44],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['#'],  pIState[0],  pIState[33]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[':'],  pIState[0],  pIState[34]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[':'],  pIState[29],  pIState[43]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[':'],  pIState[30],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[':'],  pIState[66],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['\\'],  pIState[0],  pIState[39]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['['],  pIState[0],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[']'],  pIState[0],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['('],  pIState[0],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[')'],  pIState[0],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['{'],  pIState[0],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['}'],  pIState[0],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['~'],  pIState[0],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['?'],  pIState[0],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[';'],  pIState[0],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent[','],  pIState[0],  pIState[126]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[3],  pIState[38]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[22],  pIState[42]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[42],  pIState[126]);
    // pIFA->pVTbl->AddTransition(pIFA, pIEvent['/'],  pIState[6],  pIState[39]);
    for (index = 0; index <= 255; index++) {
        if (index != '-' && index != '=' && index != '>') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[23],  pIState[151]);
        }
        if (index != '+' && index != '=') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[24],  pIState[151]);
        }
        if (index != '&' && index != '=') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[25],  pIState[151]);
        }
        if (index != '|' && index != '=') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[26],  pIState[151]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[27],  pIState[151]);
        }
        if (index != '=') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[32],  pIState[151]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[44],  pIState[151]);
        }
        if (index != '.') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[42],  pIState[151]);
        }
        if (index != '>' && index != '=') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[28],  pIState[151]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[29],  pIState[151]);
        }
        if (index != '<' && index != '=' && index != ':' && index != '%') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[30],  pIState[151]);
        }
        if (index != '<') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[44],  pIState[151]);
        }
        if (index != '#') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[33],  pIState[151]);
        }
        if (index != '>') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[31],  pIState[151]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[34],  pIState[151]);
        }
        if (index != '%') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[43],  pIState[151]);
        }
        if (index != ':') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[66],  pIState[151]);
        }
        if (index != '\"') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[66],  pIState[151]);
        }
        /* пунктуатор */
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[126],  pIState[151]);
    }

    /* Создаем переходы для констант */
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['0'],  pIState[0],  pIState[3]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['1'],  pIState[0],  pIState[4]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['2'],  pIState[0],  pIState[4]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['3'],  pIState[0],  pIState[4]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['4'],  pIState[0],  pIState[4]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['5'],  pIState[0],  pIState[4]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['6'],  pIState[0],  pIState[4]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['7'],  pIState[0],  pIState[4]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['8'],  pIState[0],  pIState[4]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['9'],  pIState[0],  pIState[4]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[0],  pIState[22]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['\''],  pIState[0],  pIState[124]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['\"'],  pIState[0],  pIState[45]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['\''],  pIState[5],  pIState[124]);
    pIFA->pVTbl->AddTransition(pIFA, pIEvent['\"'],  pIState[5],  pIState[45]);
    /* восьмиричные */
    for (index = 0; index <= 255; index++) {
        if (index >= '0' && index <= '7') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[3],  pIState[35]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[35],  pIState[35]);
            continue;
        }
        if (index == 'u' || index == 'U') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[3],  pIState[131]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[35],  pIState[131]);
            continue;
        }
        if (index == 'x' || index == 'X') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[3],  pIState[37]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[35],  pIState[131]);
            continue;
        }
        if (index == 'l') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[3],  pIState[170]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[35],  pIState[170]);
            continue;
        }
        if (index == 'L') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[3],  pIState[171]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[35],  pIState[171]);
            continue;
        }
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[3],  pIState[163]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[35],  pIState[163]);
    }
    /* десятичные */
    for (index = 0; index <= 255; index++) {
        if (index >= '0' && index <= '9') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[4],  pIState[4]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[22],  pIState[38]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[38],  pIState[38]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[140],  pIState[140]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[177],  pIState[164]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[137],  pIState[164]);
            continue;
        }
        if (index == 'u' || index == 'U') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[4],  pIState[131]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[38],  pIState[131]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[177],  pIState[164]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[137],  pIState[164]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[140],  pIState[164]);
            continue;
        }
        if (index == 'e' || index == 'E') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[4],  pIState[176]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[38],  pIState[176]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[177],  pIState[164]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[137],  pIState[164]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[140],  pIState[164]);
            continue;
        }
        if (index == 'f' || index == 'F') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[4],  pIState[163]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[38],  pIState[176]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[140],  pIState[177]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[137],  pIState[177]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[177],  pIState[164]);
            continue;
        }
        if (index == 'l') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[4],  pIState[170]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[38],  pIState[177]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[137],  pIState[177]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[140],  pIState[177]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[177],  pIState[164]);
            continue;
        }
        if (index == 'L') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[4],  pIState[171]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[38],  pIState[177]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[137],  pIState[177]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[140],  pIState[177]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[177],  pIState[164]);
            continue;
        }
        if (index == '.') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[4],  pIState[22]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[22],  pIState[164]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[140],  pIState[164]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[137],  pIState[164]);
            continue;
        }
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[4],  pIState[163]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[22],  pIState[151]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[38],  pIState[164]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[140],  pIState[164]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[137],  pIState[164]);
    }
    /* шестнадцатиричные */
    for (index = 0; index <= 255; index++) {
        if ( (index >= '0' && index <= '9') || (index >= 'A' && index <= 'F') || (index >= 'a' && index <= 'f') ) {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[37],  pIState[37]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[175],  pIState[175]);
            continue;
        }
        if (index == 'u' || index == 'U') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[37],  pIState[131]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[175],  pIState[164]);
            continue;
        }
        if (index == 'p' || index == 'P') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[175],  pIState[137]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[37],  pIState[163]);
            continue;
        }
        if (index == 'l') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[37],  pIState[170]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[175],  pIState[164]);
            continue;
        }
        if (index == 'L') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[37],  pIState[171]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[175],  pIState[164]);
            continue;
        }
        if (index == '.') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[37],  pIState[175]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[175],  pIState[164]);
            continue;
        }
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[37],  pIState[163]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[175],  pIState[164]);
    }

    for (index = 0; index <= 255; index++) {
        if (index == 'l') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[131],  pIState[132]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[132],  pIState[172]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[133],  pIState[163]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[170],  pIState[174]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[171],  pIState[163]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[172],  pIState[163]);
            continue;
        }
        if (index == 'L') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[131],  pIState[133]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[132],  pIState[163]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[133],  pIState[173]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[170],  pIState[163]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[171],  pIState[174]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[173],  pIState[163]);
            continue;
        }
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[131],  pIState[163]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[132],  pIState[163]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[133],  pIState[163]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[170],  pIState[163]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[171],  pIState[163]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[172],  pIState[163]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[173],  pIState[163]);
    }

    for (index = 0; index <= 255; index++) {
        if (index == 'u' || index == 'U') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[174],  pIState[175]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[175],  pIState[163]);
            continue;
        }
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[174],  pIState[163]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[175],  pIState[163]);
    }

    for (index = 0; index <= 255; index++) {
        if ( (index >= '0' && index <= '9') || index == '-' || index == '+') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[176],  pIState[140]);
            continue;
        }
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[176],  pIState[164]);
    }

    /* символьная константа */
    for (index = 0; index <= 255; index++) {
        if ( (index >= '0' && index <= '9') || (index >= 'a' && index <= 'z') || (index >= 'A' && index <= 'Z')) {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[45],  pIState[156]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[156],  pIState[156]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[124],  pIState[124]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[177],  pIState[166]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[125],  pIState[146]);
            continue;
        }
        if (index == '\'') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[124],  pIState[177]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[125],  pIState[146]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[177],  pIState[166]);
            continue;
        }
        if (index == '\"') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[156],  pIState[125]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[125],  pIState[146]);
            continue;
        }
        if (index == '\\') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[124],  pIState[127]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[177],  pIState[166]);
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[125],  pIState[146]);
            continue;
        }
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[125],  pIState[146]);
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[177],  pIState[166]);
        /* ловушка - ошибка */
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[156],  pIState[157]);
        /* пунктуатор */
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[124],  pIState[151]);
    }
    for (index = 0; index <= 255; index++) {
        if (index == '\'' || index == '\"' || index == '\?' || index == '\\' || index == 'a' || index == 'b' ||
            index == 'f' || index == 'n' || index == 'r' || index == 't' || index == 'v') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[127],  pIState[124]);
            continue;
        }
        if (index == 'U') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[127],  pIState[128]);
            continue;
        }
        if (index == 'u') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[127],  pIState[129]);
            continue;
        }
        /* пунктуатор */
        //pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[124],  pIState[151]);
    }

    /* ключевые слова и идентификатор */
    for (index = 0; index <= 255; index++) {
        if (index == '_') {
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[6]); // identifier
            for (y = 6; y < 123; y++) {
                if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 66) {
                    continue;
                }
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
            }
            continue;
        }
        if (index >= '0' && index <= '9') {
            for (y = 5; y < 123; y++) {
                if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 66) {
                    continue;
                }
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
            }
            continue;
        }
        if (index >= 'a' && index <= 'z') {
            if (index == 'a') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[7]);     // auto
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[9],  pIState[48]);    // case
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[49],  pIState[69]);   // char
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[61],  pIState[81]);   // static
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[68],  pIState[88]);   // break
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[71],  pIState[91]);   // default
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[73],  pIState[122]);  // float
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[87],  pIState[105]);  // volatile
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 9 || y == 49 || y == 61 ||
                        y == 66 || y == 68 || y == 71 || y == 73 || y == 87) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'b') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[8]);     // break
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[92],  pIState[108]);  // double
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 66 || y == 92) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }

            }
            if (index == 'c') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[9]);     // case char const continue
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[102],  pIState[114]); // switch
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[113],  pIState[40]);  // static
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[119],  pIState[122]); // restrict struct
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 66 || y == 102 ||
                        y == 113 || y == 119) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'd') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[10]);    // default do double
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[103],  pIState[115]); // typedef
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[112],  pIState[40]);  // signed
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 66 || y == 103 || y == 112) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }

            }
            if (index == 'e') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[11]);    // else enum extern
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[10],  pIState[51]);   // default
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[16],  pIState[58]);   // register restrict return
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[47],  pIState[68]);   // break
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[72],  pIState[94]);   // extern
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[80],  pIState[100]);  // sizeof
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[84],  pIState[103]);  // typedef
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[99],  pIState[112]);  // signed unsigned
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[103],  pIState[115]); // typedef
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[112],  pIState[40]);  // signed
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[115],  pIState[120]); // typedef
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[118],  pIState[69]);  // register
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[121],  pIState[40]);  // case continue double else inline volatile while
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 10 || y == 16 ||
                        y == 47 || y == 66 || y == 72 || y == 80 || y == 84 || y == 99 || y == 103 ||
                        y == 112 || y == 115 || y == 118 || y == 121) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }

            }
            if (index == 'f') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[12]);    // float for
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[14],  pIState[40]);   // if
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[51],  pIState[71]);   // default
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[120],  pIState[40]);  // if sizeof typedef
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 14 || y == 51 || y == 66 || y == 120) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'g') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[13]);    // goto
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[58],  pIState[76]);   // register
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[59],  pIState[6]);    // identifier
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[60],  pIState[79]);   // signed
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[75],  pIState[40]);   // long
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[104],  pIState[79]);  // unsigned
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 58 || y == 59 ||
                        y == 60 || y == 66 || y == 75 || y == 104) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'i') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[14]);    // if inline int
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[17],  pIState[60]);   // signed
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[41],  pIState[108]);  // while
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[62],  pIState[83]);   // switch
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[64],  pIState[85]);   // union
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[65],  pIState[112]);  // void
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[74],  pIState[95]);   // inline
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[76],  pIState[96]);   // register
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[86],  pIState[104]);  // unsigned
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[90],  pIState[106]);  // continue
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[101],  pIState[113]); // static
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[111],  pIState[119]); // restrict
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[116],  pIState[108]); // volatile
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 17 || y == 41 || y == 62 ||
                        y == 64 || y == 65 || y == 66 || y == 74 || y == 76 || y == 86 || y == 90 ||
                        y == 101 || y == 111 || y == 116) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }

            }
            if (index == 'h') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[9],  pIState[49]);    // char
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[17],  pIState[59]);   // short
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[21],  pIState[41]);   // while
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[40],  pIState[6]);    // identifier
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[114],  pIState[40]);  // switch
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 17 || y == 21 ||
                        y == 40 || y == 66 || y == 114) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'k') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[88],  pIState[40]);   // break
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 88 || y == 66) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'l') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[15]);    // long
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[11],  pIState[48]);   // else
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[12],  pIState[55]);   // float
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[56],  pIState[74]);   // inline
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[65],  pIState[87]);   // volatile
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[107],  pIState[122]); // default
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[108],  pIState[121]); // double
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 11 || y == 12 ||
                        y == 56 || y == 65 || y == 66 || y == 107 || y == 108) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'm') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[93],  pIState[40]);   // enum
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 93 || y == 66) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'n') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[11],  pIState[53]);   // enum
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[14],  pIState[56]);   // int
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[19],  pIState[64]);   // union
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[50],  pIState[70]);   // const
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[57],  pIState[75]);   // long
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[79],  pIState[99]);   // signed
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[95],  pIState[121]);  // inline
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[106],  pIState[117]); // continue
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[109],  pIState[40]);  // return union
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 11 || y == 14 ||
                         y == 19 || y == 50 || y == 57 || y == 66 || y == 79 || y == 95 || y == 106 || y == 109) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'o') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[9],  pIState[50]);    // const
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[10],  pIState[52]);   // do double
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[12],  pIState[69]);   // for
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[13],  pIState[46]);   // goto
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[15],  pIState[57]);   // long
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[20],  pIState[65]);   // void
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[55],  pIState[73]);   // float
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[59],  pIState[98]);   // short
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[67],  pIState[40]);   // auto
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[85],  pIState[109]);  // union
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[100],  pIState[120]); // sizeof
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 9 || y == 10 ||
                         y == 12 || y == 13 || y == 15 || y == 20 || y == 55 || y == 59 ||
                         y == 66 || y == 67 || y == 85 || y == 100) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'p') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[63],  pIState[84]);    // typedef
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 63 || y == 66) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'r') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[16]);    // register restrict return
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[8],  pIState[47]);    // break
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[61],  pIState[82]);   // struct
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[69],  pIState[40]);   // char for
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[94],  pIState[109]);  // extern
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[97],  pIState[111]);  // restrict
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[98],  pIState[122]);  // short
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[118],  pIState[69]);  // register
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 8 || y == 61 ||
                         y == 66 || y == 69 || y == 94 || y == 97 || y == 98 || y == 118) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 's') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[17]);    // short signed sizeof static struct switch
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[7],  pIState[93]);    // asm
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[48],  pIState[121]);  // case
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[58],  pIState[77]);   // restrict
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[64],  pIState[86]);   // unsigned
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[70],  pIState[122]);  // const
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[96],  pIState[110]);  // signed
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 7 || y == 48 ||
                        y == 58 || y == 64 || y == 66 || y == 70 || y == 96) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 't') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[18]);    // typedef
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[17],  pIState[61]);   // static struct
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[46],  pIState[67]);   // auto
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[54],  pIState[72]);   // extern
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[56],  pIState[40]);   // int
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[58],  pIState[78]);   // return
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[70],  pIState[90]);   // continue
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[77],  pIState[97]);   // restrict
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[81],  pIState[101]);  // static
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[83],  pIState[102]);  // switch
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[105],  pIState[116]); // volatile
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[110],  pIState[118]); // register
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[122],  pIState[40]);  // const default float restrict short struct
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 17 || y == 46 ||
                        y == 54 || y == 56 || y == 58 || y == 66 || y == 70 || y == 77 ||
                        y == 81 || y == 83 || y == 105 || y == 110 || y == 122) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'u') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[19]);    // union unsigned
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[7],  pIState[46]);    // auto
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[52],  pIState[92]);   // double
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[53],  pIState[93]);   // enum
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[78],  pIState[94]);   // return
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[82],  pIState[119]);  // struct
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[91],  pIState[107]);  // default
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[117],  pIState[121]); // continue
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 7 || y == 52 ||
                        y == 53 || y == 66 || y == 78 || y == 82 || y == 91 || y == 117) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'v') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[20]);    // void volatile
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 66) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'w') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[21]);    // while
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[17],  pIState[62]);   // switch
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 17 || y == 66) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'x') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[11],  pIState[54]);   // extern
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 11 || y == 66) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'y') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[18],  pIState[63]);   // typedef
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 18 || y == 66) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }
            if (index == 'z') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[60],  pIState[80]);   // sizeof
                for (y = 5; y < 123; y++) {
                    if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 60 || y == 66) {
                        continue;
                    }
                    pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
                }
            }

            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[6]);
            continue;
        }
        if (index >= 'A' && index <= 'Z') {
            if (index == 'L') {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[5]);
            }
            else {
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[0],  pIState[6]);
            }
            for (y = 5; y < 123; y++) {
                if ( (y >= 22 && y < 40) || (y >= 42 && y < 46) || y == 66) {
                    continue;
                }
                pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[6]);
            }
            continue;
        }
        for (y = 5; y < 123; y++) {
            if ( (y >= 22 && y <= 40) || (y >= 42 && y < 46) || y == 52 || y == 66 || (index == '\'' && y == 5 ) || (index == '\"' && y == 5 )) {
                continue;
            }
            pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[y],  pIState[144]);
        }
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[40],  pIState[145]);    // keyword
        pIFA->pVTbl->AddTransition(pIFA, pIEvent[index],  pIState[52],  pIState[145]);    // keyword
    }



    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[4],  pIState[143]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[16],  pIState[6]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[16],  pIState[6]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[56],  pIState[6]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[38],  pIState[143]);

    //for (index = 0; index < 27; index++) {
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[pszPunctuators[index]],  pIState[40],  pIState[145]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[pszPunctuators[index]],  pIState[89],  pIState[145]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[pszPunctuators[index]],  pIState[38],  pIState[164]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[pszPunctuators[index]],  pIState[4],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[pszPunctuators[index]],  pIState[126],  pIState[151]);
    //    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[pszPunctuators[index]],  pIState[157],  pIState[158]);
    //}

    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\"'],  pIState[0],  pIState[45]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[0],  pIState[5]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[0],  pIState[2]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[2],  pIState[2]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[2],  pIState[2]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[0],  pIState[5]);

    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[0],  pIState[22]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['-'],  pIState[0],  pIState[23]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['+'],  pIState[0],  pIState[24]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['&'],  pIState[0],  pIState[25]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['*'],  pIState[0],  pIState[26]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['!'],  pIState[0],  pIState[26]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['^'],  pIState[0],  pIState[26]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['|'],  pIState[0],  pIState[27]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['/'],  pIState[0],  pIState[28]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['%'],  pIState[0],  pIState[29]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['<'],  pIState[0],  pIState[30]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[0],  pIState[31]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[0],  pIState[32]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['#'],  pIState[0],  pIState[33]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[':'],  pIState[0],  pIState[34]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\\'],  pIState[0],  pIState[39]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['['],  pIState[0],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[']'],  pIState[0],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['('],  pIState[0],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[')'],  pIState[0],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['{'],  pIState[0],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['}'],  pIState[0],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['~'],  pIState[0],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['?'],  pIState[0],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[';'],  pIState[0],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[','],  pIState[0],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[3],  pIState[38]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['/'],  pIState[6],  pIState[39]);

    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['-'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['+'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['&'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['*'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['!'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['^'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['|'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['%'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['<'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['#'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent[':'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['\\'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['['],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent[']'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['('],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent[')'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['{'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['}'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['~'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['?'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent[';'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent[','],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[6],  pIState[144]);
    ////pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[6],  pIState[144]);

    //for (index = 3; index <= 4; index++) {
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[index],  pIState[38]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['-'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['+'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['&'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['*'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['!'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['^'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['|'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['%'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['<'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['#'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[':'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['\\'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['['],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[']'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['('],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[')'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['{'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['}'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['~'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['?'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[';'],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[','],  pIState[index],  pIState[143]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[index],  pIState[143]);
    //}


    //for (index = 6; index <= 122; index++) {
    //    if (index >= 22 && index < 41 || index == 89) {
    //        continue;
    //    }
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['-'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['+'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['&'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['*'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['!'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['^'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['|'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['%'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['<'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['#'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[':'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['\\'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['['],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[']'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['('],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[')'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['{'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['}'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['~'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['?'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[';'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[','],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[index],  pIState[144]);
    //    pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[index],  pIState[144]);
    //}
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[7],  pIState[46]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[8],  pIState[47]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[9],  pIState[48]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[9],  pIState[49]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[9],  pIState[50]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[10],  pIState[51]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[10],  pIState[52]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[11],  pIState[48]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[11],  pIState[53]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['x'],  pIState[11],  pIState[54]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[12],  pIState[69]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[12],  pIState[55]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[13],  pIState[46]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['f'],  pIState[14],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[14],  pIState[56]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[15],  pIState[57]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[16],  pIState[58]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[17],  pIState[59]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[17],  pIState[60]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[17],  pIState[61]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['w'],  pIState[17],  pIState[62]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['y'],  pIState[18],  pIState[63]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[19],  pIState[64]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[20],  pIState[65]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[21],  pIState[41]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[22],  pIState[137]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['E'],  pIState[22],  pIState[137]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['f'],  pIState[22],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['F'],  pIState[22],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[22],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[22],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[22],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[')'],  pIState[22],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[22],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[22],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[22],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[22],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[23],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['-'],  pIState[23],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[23],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[23],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[23],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[23],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[23],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['+'],  pIState[24],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[24],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[24],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[24],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[24],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[24],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['&'],  pIState[25],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[25],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[25],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[25],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[25],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[25],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['|'],  pIState[26],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[26],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[26],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[26],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[26],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[26],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['*'],  pIState[26],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[';'],  pIState[26],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['('],  pIState[26],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[','],  pIState[26],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[27],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[27],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[27],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[27],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[27],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['*'],  pIState[28],  pIState[152]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[28],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[28],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[28],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[28],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[28],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[28],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[':'],  pIState[29],  pIState[43]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[29],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[29],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[29],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[29],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[29],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[29],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[':'],  pIState[30],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['%'],  pIState[30],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[30],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['<'],  pIState[30],  pIState[44]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[30],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[30],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[30],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[30],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[31],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[31],  pIState[44]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[31],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[31],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[31],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[31],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[32],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[32],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[32],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[32],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[32],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['#'],  pIState[33],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[33],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[33],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[33],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[33],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[159],  pIState[160]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[159],  pIState[160]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['>'],  pIState[34],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[34],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[34],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[34],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[34],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[35],  pIState[131]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['U'],  pIState[35],  pIState[131]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[35],  pIState[132]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[35],  pIState[132]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['.'],  pIState[35],  pIState[38]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['_'],  pIState[36],  pIState[148]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['#'],  pIState[36],  pIState[148]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[36],  pIState[148]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[36],  pIState[148]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[36],  pIState[148]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[36],  pIState[148]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[38],  pIState[131]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['U'],  pIState[38],  pIState[131]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\\'],  pIState[39],  pIState[45]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\''],  pIState[39],  pIState[45]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['"'],  pIState[39],  pIState[45]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['?'],  pIState[39],  pIState[45]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[39],  pIState[45]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['b'],  pIState[39],  pIState[45]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['f'],  pIState[39],  pIState[45]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[39],  pIState[45]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[39],  pIState[45]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[39],  pIState[45]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['v'],  pIState[39],  pIState[45]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[39],  pIState[150]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[39],  pIState[150]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[40],  pIState[145]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[40],  pIState[145]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[40],  pIState[145]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[' '],  pIState[40],  pIState[145]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[';'],  pIState[40],  pIState[145]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[41],  pIState[108]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['%'],  pIState[43],  pIState[66]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['='],  pIState[44],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['"'],  pIState[45],  pIState[125]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[46],  pIState[67]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[47],  pIState[68]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[48],  pIState[121]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[49],  pIState[69]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[50],  pIState[70]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['f'],  pIState[51],  pIState[71]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[52],  pIState[92]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[52],  pIState[145]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[52],  pIState[145]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[53],  pIState[93]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[54],  pIState[72]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[55],  pIState[73]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[56],  pIState[74]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[56],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[57],  pIState[75]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['g'],  pIState[58],  pIState[76]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[58],  pIState[77]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[58],  pIState[78]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[59],  pIState[98]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['g'],  pIState[60],  pIState[79]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['z'],  pIState[60],  pIState[80]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[61],  pIState[81]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[61],  pIState[82]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[62],  pIState[83]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[63],  pIState[84]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[64],  pIState[85]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[64],  pIState[86]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[65],  pIState[87]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[65],  pIState[112]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[':'],  pIState[66],  pIState[126]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[67],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[68],  pIState[88]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[69],  pIState[89]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[70],  pIState[122]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[70],  pIState[90]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[71],  pIState[91]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[72],  pIState[94]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[73],  pIState[122]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[74],  pIState[95]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['g'],  pIState[75],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[76],  pIState[96]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[77],  pIState[97]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[78],  pIState[94]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[79],  pIState[99]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[80],  pIState[100]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[81],  pIState[101]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[82],  pIState[119]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[83],  pIState[102]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[84],  pIState[103]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[85],  pIState[109]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[86],  pIState[104]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[87],  pIState[105]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['k'],  pIState[88],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[89],  pIState[145]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[89],  pIState[145]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[90],  pIState[106]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[91],  pIState[107]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['b'],  pIState[92],  pIState[108]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['m'],  pIState[93],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[94],  pIState[109]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[95],  pIState[121]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['s'],  pIState[96],  pIState[110]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[97],  pIState[111]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[98],  pIState[122]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[99],  pIState[112]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['o'],  pIState[100],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[101],  pIState[113]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[102],  pIState[114]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[103],  pIState[115]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['g'],  pIState[104],  pIState[79]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[105],  pIState[116]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[106],  pIState[117]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[107],  pIState[122]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[108],  pIState[145]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[108],  pIState[145]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[109],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[110],  pIState[118]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[111],  pIState[119]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['d'],  pIState[112],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[113],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['h'],  pIState[114],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[115],  pIState[120]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['i'],  pIState[116],  pIState[108]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[117],  pIState[121]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[118],  pIState[69]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['c'],  pIState[119],  pIState[122]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['f'],  pIState[120],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['e'],  pIState[121],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[122],  pIState[40]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[123],  pIState[131]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['U'],  pIState[123],  pIState[131]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\\'],  pIState[124],  pIState[127]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\''],  pIState[0],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\''],  pIState[124],  pIState[167]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[125],  pIState[146]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[125],  pIState[146]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[126],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[126],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[126],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[126],  pIState[151]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['U'],  pIState[127],  pIState[128]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[127],  pIState[129]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['x'],  pIState[127],  pIState[130]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\\'],  pIState[127],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\''],  pIState[127],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['"'],  pIState[127],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['?'],  pIState[127],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['a'],  pIState[127],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['b'],  pIState[127],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['f'],  pIState[127],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['n'],  pIState[127],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['r'],  pIState[127],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['t'],  pIState[127],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['v'],  pIState[127],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\''],  pIState[128],  pIState[124]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[132],  pIState[133]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[132],  pIState[133]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[132],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['U'],  pIState[132],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['u'],  pIState[133],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['U'],  pIState[133],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[131],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[131],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['l'],  pIState[134],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['L'],  pIState[134],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['f'],  pIState[134],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['F'],  pIState[134],  pIState[142]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['p'],  pIState[134],  pIState[137]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['P'],  pIState[134],  pIState[137]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['+'],  pIState[137],  pIState[140]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['-'],  pIState[137],  pIState[140]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[142],  pIState[143]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[142],  pIState[143]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[142],  pIState[143]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[142],  pIState[143]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['*'],  pIState[152],  pIState[154]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['/'],  pIState[154],  pIState[155]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\"'],  pIState[156],  pIState[157]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\"'],  pIState[160],  pIState[161]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent['\"'],  pIState[161],  pIState[162]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[157],  pIState[146]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[157],  pIState[146]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[157],  pIState[146]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[157],  pIState[146]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[';'],  pIState[157],  pIState[146]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[32],  pIState[167],  pIState[166]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[9],  pIState[167],  pIState[166]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[10],  pIState[167],  pIState[166]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[13],  pIState[167],  pIState[166]);
    //pIFA->pVTbl->AddTransition(pIFA, pIEvent[';'],  pIState[167],  pIState[166]);
    return pIFA;
}


/*
 *
 * <сводка>
 *   Функция GetBNFForSAOfC89
 * </сводка>
 *
 * <описание>
 *   Функция GetBNFForSAOfC89 - возвращает контекстно-свободную грамматику в BNF форме для синтаксического анализа C89
 * </описание>
 *
 */
IEcoToolchainBNF1* GetBNFForSAOfC89(IEcoToolchainBNF1* pIBNF) {
    /* Интерфейсы для работы с грамматикой */
    IEcoToolchainBNF1Rule* pIRule = 0;
    IEcoToolchainBNF1Element* pIElement = 0;
    uint32_t indexSet = 0;
    bool_t bOptFALSE = 0;
    bool_t bOptTRUE = 1;

    /* Beginning */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "c0-begin-state");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "translation-unit", bOptFALSE, &indexSet);

    /* A.2.1 Expressions */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "primary-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "identifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "constant", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "string-literal", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "(", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);

	pIRule = pIBNF->pVTbl->AddRule(pIBNF, "constant");
	pIElement = pIRule->pVTbl->AddAlternative(pIRule, "integer-constant", bOptFALSE, &indexSet);
	pIElement = pIRule->pVTbl->AddAlternative(pIRule, "character-constant", bOptFALSE, &indexSet);
	pIElement = pIRule->pVTbl->AddAlternative(pIRule, "floating-constant", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "postfix-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "primary-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "postfix-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "[", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "]", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "postfix-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "(", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "argument-expression-list", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "postfix-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ".", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "identifier", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "postfix-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "->", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "identifier", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "postfix-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "++", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "postfix-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "--", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "(", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "type-name", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "{", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "initializer-list", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "}", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "(", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "type-name", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "{", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "initializer-list", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "}", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "argument-expression-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "assignment-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "argument-expression-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "assignment-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "unary-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "postfix-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "++", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "unary-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "--", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "unary-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "unary-operator", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "cast-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "sizeof", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "unary-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "sizeof", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "(", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "type-name", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "unary-operator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "&", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "*", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "+", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "-", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "~", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "!", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "cast-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "unary-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "(", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "type-name", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "cast-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "multiplicative-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "cast-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "multiplicative-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "*", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "cast-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "multiplicative-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "/", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "cast-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "multiplicative-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "%", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "cast-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "additive-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "multiplicative-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "additive-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "+", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "multiplicative-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "additive-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "-", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "multiplicative-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "shift-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "additive-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "shift-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "<<", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "additive-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "shift-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ">>", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "additive-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "relational-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "shift-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "relational-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "<", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "shift-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "relational-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ">", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "shift-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "relational-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "<=", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "shift-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "relational-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ">=", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "shift-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "equality-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "relational-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "equality-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "==", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "relational-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "equality-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "!=", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "relational-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "AND-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "equality-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "AND-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "&", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "equality-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "exclusive-OR-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "AND-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "exclusive-OR-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "^", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "AND-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "inclusive-OR-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "exclusive-OR-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "inclusive-OR-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "|", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "exclusive-OR-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "logical-AND-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "inclusive-OR-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "logical-AND-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "&&", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "inclusive-OR-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "logical-OR-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "logical-AND-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "logical-OR-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "||", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "logical-AND-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "conditional-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "logical-OR-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "logical-OR-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "?", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ":", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "conditional-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "assignment-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "conditional-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "unary-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "assignment-operator", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "assignment-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "assignment-operator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "=", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "*=", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "/=", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "%=", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "+=", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "-=", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "<<=", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, ">>=", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "&=", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "^=", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "|=", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "assignment-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "assignment-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "constant-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "conditional-expression", bOptFALSE, &indexSet);

    /* A.2.2 Declarations */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declaration-specifier", bOptFALSE, &indexSet);  //declaration-specifiers
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "init-declarator-list", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ";", bOptFALSE);

    // Rule for mapping declaration-specifier
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration-specifier");                                     
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declaration-specifiers", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration-specifiers");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "storage-class-specifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "declaration-specifiers", bOptTRUE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "type-specifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "declaration-specifiers", bOptTRUE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "type-qualifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "declaration-specifiers", bOptTRUE);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "function-specifier", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "declaration-specifiers", bOptTRUE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "init-declarator-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "init-declarator", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "init-declarator-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "init-declarator", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "init-declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declarator", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declarator", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "=", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "initializer", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "storage-class-specifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "typedef", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "extern", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "static", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "auto", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "register", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type-specifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "void", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "char", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "short", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "int", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "long", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "float", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "double", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "signed", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "unsigned", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "_Bool", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "_Complex", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "struct-or-union-specifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "enum-specifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "typedef-name", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-or-union-specifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "struct-or-union", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "identifier", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "{", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "struct-declaration-list", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "}", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "struct-or-union", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "identifier", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-or-union");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "struct", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "union", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-declaration-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "struct-declaration", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "struct-declaration-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "struct-declaration", bOptFALSE);

	// Rule for mapping specifier-qualifier
	pIRule = pIBNF->pVTbl->AddRule(pIBNF, "specifier-qualifier");
	pIElement = pIRule->pVTbl->AddAlternative(pIRule, "specifier-qualifier-list", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-declaration");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "specifier-qualifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "struct-declarator-list", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ";", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "specifier-qualifier-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "type-specifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "specifier-qualifier-list", bOptTRUE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "type-qualifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "specifier-qualifier-list", bOptTRUE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-declarator-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "struct-declarator", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "struct-declarator-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "struct-declarator", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declarator", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declarator", bOptTRUE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ":", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "constant-expression", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "enum-specifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "enum", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "identifier", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "{", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "enumerator-list", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "}", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "enum", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "identifier", bOptTRUE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "{", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "enumerator-list", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "}", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "enum", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "identifier", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "enumerator-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "enumerator", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "enumerator-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "enumerator", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "enumerator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "enumeration-constant", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "enumeration-constant", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "=", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "constant-expression", bOptFALSE);

    /* Add rule from lexical grammar */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "enumeration-constant");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "identifier", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type-qualifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "const", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "restrict", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "volatile", bOptFALSE, &indexSet);

    //pIRule = pIBNF->pVTbl->AddRule(pIBNF, "function-specifier");
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "inline", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "pointer", bOptTRUE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "direct-declarator", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "direct-declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "identifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "(", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "declarator", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "direct-declarator", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "[", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "type-qualifier-list", bOptTRUE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "assignment-expression", bOptTRUE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "]", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "direct-declarator", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "[", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "static", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "type-qualifier-list", bOptTRUE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "assignment-expression", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "]", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "direct-declarator", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "[", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "type-qualifier-list", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "static", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "assignment-expression", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "]", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "direct-declarator", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "[", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "type-qualifier-list", bOptTRUE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "*", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "]", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "direct-declarator", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "[", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "constant-expression", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "]", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "direct-declarator", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "(", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "parameter-type-list", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "direct-declarator", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "(", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "identifier-list", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "pointer");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "*", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "type-qualifier-list", bOptTRUE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "*", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "type-qualifier-list", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "pointer", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type-qualifier-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "type-qualifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "type-qualifier-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "type-qualifier", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "parameter-type-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "parameter-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "parameter-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptFALSE);
	pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "...", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "parameter-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "parameter-declaration", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "parameter-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "parameter-declaration", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "parameter-declaration");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declaration-specifier", bOptFALSE, &indexSet);  // declaration-specifiers
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "declarator", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declaration-specifier", bOptFALSE, &indexSet);  // declaration-specifiers
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "abstract-declarator", bOptTRUE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "identifier-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "identifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "identifier-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "identifier", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type-name");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "specifier-qualifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "abstract-declarator", bOptTRUE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "abstract-declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "pointer", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "pointer", bOptTRUE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "direct-abstract-declarator", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "direct-abstract-declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "(", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "abstract-declarator", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "direct-abstract-declarator", bOptTRUE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "[", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "assignment-expression", bOptTRUE);     
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "]", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "direct-abstract-declarator", bOptTRUE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "[", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "*", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "]", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "direct-abstract-declarator", bOptTRUE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "[", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "constant-expression", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "]", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "direct-abstract-declarator", bOptTRUE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "(", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "parameter-type-list", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "typedef-name");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "identifier", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "initializer");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "assignment-expression", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "{", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "initializer-list", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "}", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "{", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "initializer-list", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "}", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "initializer-list");
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "designation", bOptTRUE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "initializer", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "initializer", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "initializer-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "designation", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "initializer", bOptFALSE);

    //pIRule = pIBNF->pVTbl->AddRule(pIBNF, "designation");
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "designator-list", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "=", bOptFALSE);

    //pIRule = pIBNF->pVTbl->AddRule(pIBNF, "designator-list");
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "designator", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "designator-list", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "designator", bOptFALSE);

    //pIRule = pIBNF->pVTbl->AddRule(pIBNF, "designator");
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "[", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "constant-expression", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "]", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, ".", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "identifier", bOptFALSE);

    /* A.2.3 Statements */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "labeled-statement", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "compound-statement", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "expression-statement", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "selection-statement", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "iteration-statement", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "jump-statement", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "labeled-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "identifier", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ":", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "case", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "constant-expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ":", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "default", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ":", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "compound-statement");
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "{", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "block-item-list", bOptTRUE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "}", bOptFALSE);

    //pIRule = pIBNF->pVTbl->AddRule(pIBNF, "block-item-list");
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "block-item", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "block-item-list", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "block-item", bOptFALSE);

    //pIRule = pIBNF->pVTbl->AddRule(pIBNF, "block-item");
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declaration", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "statement", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "{", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "declaration-list", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement-list", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "}", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declaration", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declaration-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "declaration", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "statement-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "statement", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "statement-list", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "expression-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "expression", bOptTRUE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ";", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "selection-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "if", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "(", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "if", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "(", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "else", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "switch", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "(", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "iteration-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "while", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "(", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "do", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "while", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "(", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ";", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "for", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "(", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ";", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ";", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "for", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "(", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "declaration", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptTRUE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ";", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptTRUE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ")", bOptFALSE);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "statement", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "jump-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "goto", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "identifier", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ";", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "continue", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ";", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "break", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ";", bOptFALSE);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "return", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "expression", bOptTRUE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ";", bOptFALSE);

    /* A.2.4 External definitions */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "translation-unit");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "external-declaration", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "translation-unit", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "external-declaration", bOptFALSE);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "external-declaration");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "function-definition", bOptFALSE, &indexSet);
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declaration", bOptFALSE, &indexSet);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "function-definition");
	pIElement = pIRule->pVTbl->AddAlternative(pIRule, "function-definition-specifier", bOptFALSE, &indexSet);
	pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "compound-statement", bOptFALSE);

	pIRule = pIBNF->pVTbl->AddRule(pIBNF, "function-definition-specifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declaration-specifier", bOptTRUE, &indexSet); //declaration-specifiers
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "declarator", bOptFALSE);
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "declaration-list", bOptTRUE);

    //pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration-list");
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declaration", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, "declaration-list", bOptFALSE, &indexSet);
    //pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "declaration", bOptFALSE);

    return pIBNF;
}