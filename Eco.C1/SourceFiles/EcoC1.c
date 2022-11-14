/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoC1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoInterfaceBus1.h"
#include "IdEcoString1.h"
#include "IdEcoStack1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoToolchainPushdownAutomata1.h"
#include "IdEcoToolchainLexicalAnalyzer1.h"
#include "IdEcoToolchainSyntaxAnalyzer1.h"
//#include "IdEcoToolchainLALR1.h"
//#include "IdEcoToolchainSLR1.h"
#include "IdEcoToolchainLR1.h"
#include "IdEcoToolchainAST1.h"
#include "IdEcoToolchainBNF1.h"
#include "IdEcoToolchainMacroProcessor1.h"
#include "IdEcoToolchainCodeGenerator1.h"
#include "IdEcoToolchainEmitterI8086.h"
#include "IdEcoToolchainEmitterI80686.h"
#include "IdEcoToolchainLinker1.h"
#include "IdEcoOMF1.h"
#include "IdEcoPECOFF1.h"
#include "IdEcoFSM1.h"
#include "IdEcoLog1.h"
#include "IdEcoList1.h"
#include "IEcoLog1FileAffiliate.h"
#include "EcoAsm8086Grammar.h"
#include "EcoC89Grammar.h"
#include "EcoOutputDiagnostic.h"

#include <stdio.h>

void removeChar(char_t* pStr, char_t ch) {
    char_t* pRes = pStr;

    if (pStr == 0) {
        return;
    }

    while (*pStr) {
        if (*pStr != ch)
            *pRes++ = *pStr;
        pStr++;
    }
    *pRes = '\0';
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на интерфейс работы сo строкой */
    IEcoString1* pIStr = 0;
    /* Указатель на интерфейс работы с журналом */
    IEcoLog1* pILog = 0;
    IEcoLog1FileAffiliate* pIFileAffiliate = 0;
    /* Указатель на интерфейс работы с фйалами */
    IEcoFileManager1* pIFileManager = 0;
    IEcoList1* pISourceFiles = 0;
    uint32_t iSourceIndex = 0;
    char_t* pszSearchFileName = 0;
    char_t* pszSourceFileName = 0;
    char_t* pszSourceFileExt = 0;
    char_t* pszSourceName = 0;
    char_t* pszObjName = 0;
    /* Интерфейсы для работы с грамматикой */
    IEcoToolchainBNF1* pIC89GrammarLex = 0;
    IEcoToolchainBNF1* pIC89GrammarSyn = 0;
    IEcoToolchainBNF1* pIAsmGrammarLex = 0;
    IEcoToolchainBNF1* pIAsmGrammarSyn = 0;
    IEcoToolchainBNF1Rule* pIRule = 0;
    IEcoToolchainBNF1Element* pIElement = 0;
    uint32_t indexSet = 0;
    bool_t bOptional = 0;
    /* Интерфейсы для работы с лексическим анализом */
    IEcoToolchainLexicalAnalyzer1* pILexer = 0;
    IEcoToolchainLexicalAnalyzer1Scanner* pIScanner = 0;
    IEcoToolchainLexicalAnalyzer1Token* pIToken = 0;
    IEcoToolchainLexicalAnalyzer1Token* pIOutToken = 0;
    IEcoToolchainLexicalAnalyzer1Token* pIPreToken = 0;
    IEcoStack1* pIScannerList = 0;
    IEcoStack1* pITokenList = 0;
    uint32_t iTokenIndex = 0;
    /* Интерфейсы для работы с синтаксическим анализом */
    IEcoToolchainSyntaxAnalyzer1* pISyntax = 0;
    IEcoToolchainSyntaxAnalyzer1Parser* pIAsmParser = 0;
    IEcoToolchainSyntaxAnalyzer1Parser* pIC89Parser = 0;
    IEcoToolchainSyntaxAnalyzer1Parser* pIParser = 0;
    IEcoUnknown* pIUnkAlgorithm = 0;
    IEcoToolchainParser1LRk* pILRkAlgorithm = 0;
    IEcoToolchainParser1Action* pIAction = 0;
    /* Интерфейсы для работы с препроцессором */
    IEcoToolchainMacroProcessor1* pIAsmPreprocessor = 0;
    IEcoToolchainMacroProcessor1* pIC89Preprocessor = 0;
    IEcoToolchainMacroProcessor1* pIPreprocessor = 0;
    IEcoList1* pIMacroExpTokenList = 0;
    IEcoToolchainMacroProcessor1Processing* pIPreProcessing = 0;
    IEcoToolchainMacroProcessor1Result* pIPreResult = 0;
    /* Интерфейсы для работы с абстрактным синтаксическим деревом */
    IEcoToolchainAST1* pIAST = 0;
    IEcoFSM1* pIFSM = 0;
    IEcoFSM1StateMachine* pIFA = 0;
    IEcoToolchainCodeGenerator1* pICodeGen = 0;
    IEcoToolchainEmitter1* pIEmitter = 0;
    IEcoToolchainLinker1* pILinker = 0;
    IEcoList1* pIObjFiles = 0;
    /* Переменные входного потока */
    char_t inputAsmStream[256] = {'M', 'O', 'V', ' ', 'A', 'L', ',', 'B', 'L', '\n', '\0'};
    uint32_t inputAsmSize = 256;
    uint16_t iActiveLang = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
            /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса для работы со строкой */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void **)&pIStr);
    if (result != 0 || pIStr == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**)&pIMem);
    if (result != 0 || pIMem == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса для работы с журналом */
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLog1, 0, &IID_IEcoLog1, (void**) &pILog);
    if (result != 0|| pILog == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLog1, 0, &IID_IEcoLog1FileAffiliate, (void**) &pIFileAffiliate);
    if (result != 0|| pIFileAffiliate == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    pILog->pVTbl->AddAffiliate(pILog, (IEcoLog1Affiliate*)pIFileAffiliate);
    pIFileAffiliate->pVTbl->Release(pIFileAffiliate);

    /* Получение интерфейса для работы с конечным автоматом */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoFSM1, 0, &IID_IEcoFSM1, (void **)&pIFSM);
    if (result != 0 || pIFSM == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /******************************************************************************************** НАСТРОЙКА ********************************************************************************************/

    /* Получение интерфейса управление файлами */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoFileSystemManagement1, 0, &IID_IEcoFileManager1, (void**) &pIFileManager);
    if (result != 0 || pIFileManager == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса по работе со списком сканеров */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoStack1, 0, &IID_IEcoStack1, (void**) &pIScannerList);
    /* Проверка */
    if (result != 0 || pIScannerList == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса по работе со списком сканеров */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoStack1, 0, &IID_IEcoStack1, (void**)&pITokenList);
    /* Проверка */
    if (result != 0 || pITokenList == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса по работе со списком исходных файлов */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**) &pISourceFiles);
    /* Проверка */
    if (result != 0 || pISourceFiles == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Добавляем исходные файлы в список для компиляции под Windows */
    pISourceFiles->pVTbl->Add(pISourceFiles, "..\\..\\..\\TestFiles\\Windows\\main.c");

    /* Добавляем исходные файлы в список для компиляции под "голое железо" */
    //pISourceFiles->Add(pISourceFiles, "..\\..\\..\\TestFiles\\IBMPCx86\\test_8086_en.asm");
    //pISourceFiles->pVTbl->Add(pISourceFiles, "..\\..\\..\\TestFiles\\IBMPCx86\\main.c");
    //pISourceFiles->Add(pISourceFiles, "entry.S");
    //pISourceFiles->Add(pISourceFiles, "main.c");

    /* Получение интерфейса по работе со списком  для объектных файлов */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**) &pIObjFiles);
    /* Проверка */
    if (result != 0 || pIObjFiles == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    ///* Получение интерфейса по работе с грамматикой лексического разбора ассемблера */
    //result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoToolchainBNF1, 0, &IID_IEcoToolchainBNF1, (void**) &pIAsmGrammarLex);
    ///* Проверка */
    //if (result != 0 || pIAsmGrammarLex == 0) {
    //    /* Освобождение в случае ошибки */
    //    goto Release;
    //}

    /* ВАРИАНТ 1: Формирование правил лексического анализа для ассемблера с помощью конечного автомата */
    //pIFA = GetFAForLAOfAsm8086(pIFSM);
    /* Вывод диагностической/отладочной информации */
    //OutputDiagnosticInfoOfFA(ECO_LANG_ASM, pILog, pIStr, pIFA);
    /* ИЛИ */
    /* ВАРИАНТ 2: Формирование правил лексического анализа для ассемблера с помощью регулярной грамматики */
    //pIRG = GetRGForLAOfAsm8086();
    /* ИЛИ */
    /* ВАРИАНТ 3: Формирование правил лексического анализа для ассемблера с помощью регулярных выражений */
    //pIRE = GetREForLAOfAsm8086();
    /* ИЛИ */
    /* ВАРИАНТ 4: Формирование правил лексического анализа для ассемблера с помощью BNF формы - описывающий как регулярную грамматику так и контекстно-свободную грамматику */
    //pIBNF = GetBNFForLAOfAsm8086();
    /* Вывод диагностической/отладочной информации */
    //OutputDiagnosticInfoOfBNF(ECO_LANG_ASM, pILog, pIStr, pIAsmGrammarLex);

    /* Получение интерфейса по работе с грамматикой лексического разбора C89 */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoToolchainBNF1, 0, &IID_IEcoToolchainBNF1, (void**) &pIC89GrammarLex);
    /* Проверка */
    if (result != 0 || pIC89GrammarLex == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* ВАРИАНТ 1: Формирование правил лексического анализа для C89 с помощью конечного автомата */
    pIFA = GetFAForLAOfC89(pIFSM);
    /* Вывод диагностической/отладочной информации */
    OutputDiagnosticInfoOfFA(ECO_LANG_C89, pILog, pIStr, pIFA);
    /* ИЛИ */
    /* ВАРИАНТ 2: Формирование правил лексического анализа для C89 с помощью регулярной грамматики */
    //pIRG = GetRGForLAOfC89();
    /* ИЛИ */
    /* ВАРИАНТ 3: Формирование правил лексического анализа для C89 с помощью регулярных выражений */
    //pIRE = GetREForLAOfC89();
    /* ИЛИ */
    /* ВАРИАНТ 4: Формирование правил лексического анализа для C89 с помощью BNF формы - описывающий как регулярную грамматику так и контекстно-свободную грамматику */
    //pIBNF = GetBNFForLAOfC89();
    /* Вывод диагностической/отладочной информации */
    //OutputDiagnosticInfoOfGrammar(ECO_LANG_C89, pILog, pIStr, pIC89GrammarLex);


    /* Получение интерфейса по работе с лексическим анализом */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoToolchainLexicalAnalyzer1, 0, &IID_IEcoToolchainLexicalAnalyzer1, (void**) &pILexer);
    /* Проверка */
    if (result != 0 || pILexer == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    //    /* Получение интерфейса по работе с препроцессором для ассемблера */
    //    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoToolchainMacroProcessor1, 0, &IID_IEcoToolchainMacroProcessor1, (void**) &pIAsmPreprocessor);
    //    /* Проверка */
    //    if (result != 0 || pIAsmPreprocessor == 0) {
    //        /* Освобождение в случае ошибки */
    //        goto Release;
    //    }
    //
    //    /* Настройка препроцессора для ассемблера */
    //    pIAsmPreprocessor->pVTbl->set_InvocationCommand(pIAsmPreprocessor, ECO_MACROPROCESSOR_COMMAND_INCLUDE, ".include");
    //
    /* Получение интерфейса по работе с препроцессором для C89 */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoToolchainMacroProcessor1, 0, &IID_IEcoToolchainMacroProcessor1, (void**) &pIC89Preprocessor);
    /* Проверка */
    if (result != 0 || pIC89Preprocessor == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Настройка препроцессора для C89 */
    pIC89Preprocessor->pVTbl->set_InvocationCommand(pIC89Preprocessor, ECO_MACROPROCESSOR_COMMAND_INCLUDE, "#include");
    pIC89Preprocessor->pVTbl->Predefine(pIC89Preprocessor, "ECO_LIB", "1");

    /* Настраиваем препроцессорную обработку удаления токенов не используемых в синтаксическом анализе */
    /* Удаление комментариев comment */
    pIC89Preprocessor->pVTbl->set_DeletitionCommandByTokenId(pIC89Preprocessor, 147);
    /* Удаление новой строки new-line */
    pIC89Preprocessor->pVTbl->set_DeletitionCommandByTokenId(pIC89Preprocessor, 148);
    /* Удаление пробелов white-space */
    pIC89Preprocessor->pVTbl->set_DeletitionCommandByTokenId(pIC89Preprocessor, 149);

    /* Получение интерфейса по работе с синтаксическим анализом */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoToolchainSyntaxAnalyzer1, 0, &IID_IEcoToolchainSyntaxAnalyzer1, (void**) &pISyntax);
    /* Проверка */
    if (result != 0 || pISyntax == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация алгоритма для анализа */
    //pISyntax->pVTbl->RegisterAlgorithm(pISyntax, &CID_EcoToolchainLALR1, "LALR");
    //pISyntax->pVTbl->RegisterAlgorithm(pISyntax, &CID_EcoToolchainSLR1, "SLR");
    pISyntax->pVTbl->RegisterAlgorithm(pISyntax, &CID_EcoToolchainLR1, "LR1");
    /* Устанавливаем алгоритм по умолчанию */
    pISyntax->pVTbl->set_DefaultAlgorithm(pISyntax, "LR1");

    //    /* Получение интерфейса по работе с грамматикой синтаксического разбора ассемблера */
    //    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoToolchainBNF1, 0, &IID_IEcoToolchainBNF1, (void**) &pIAsmGrammarSyn);
    //    /* Проверка */
    //    if (result != 0 || pIAsmGrammarSyn == 0) {
    //        /* Освобождение в случае ошибки */
    //        goto Release;
    //    }

    //    /* Формирование правил синтаксического анализа для ассемблера */
    //    pIRule = pIAsmGrammarSyn->pVTbl->AddRule(pIAsmGrammarSyn, "instruction");
    //    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "opcode", bOptional, &indexSet);
    //    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "opcode", bOptional, &indexSet);
    //    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "reg", bOptional);
    //    pIElement = pIRule->pVTbl->AddAlternative(pIRule, "opcode", bOptional, &indexSet);
    //    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "reg", bOptional);
    //    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ",", bOptional);
    //    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, "reg", bOptional);
    //    /* ... */

    //    /* Получение интерфейса синтаксического разбора согласно заданным правилам для ассемблера */
    //    pIAsmParser = pISyntax->pVTbl->get_Parser(pISyntax, pIAsmGrammarSyn, 0);

    /* Получение интерфейса по работе с грамматикой синтаксического разбора C89 */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoToolchainBNF1, 0, &IID_IEcoToolchainBNF1, (void**) &pIC89GrammarSyn);
    /* Проверка */
    if (result != 0 || pIC89GrammarSyn == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }


    /* Формирование правил синтаксического анализа для C89 */
    pIC89GrammarSyn = GetBNFForSAOfC89(pIC89GrammarSyn);
    /* Вывод диагностической/отладочной информации */
    OutputDiagnosticInfoOfBNF(ECO_LANG_C89, pILog, pIStr, pIC89GrammarSyn);

    /* Получение интерфейса синтаксического разбора согласно заданным правилам для C89 */
    pIC89Parser = pISyntax->pVTbl->get_Parser(pISyntax, pIC89GrammarSyn, 0);
    /* Получение интерфейса алгоритма синтаксического разбора */
    pIUnkAlgorithm = pIC89Parser->pVTbl->get_Algorithm(pIC89Parser);
    result = pIUnkAlgorithm->pVTbl->QueryInterface(pIUnkAlgorithm, &IID_IEcoToolchainParser1LRk, (void**) &pILRkAlgorithm);
    /* Проверка */
    if (result == 0 && pILRkAlgorithm != 0) {
        /* Вывод диагностической/отладочной информации */
        OutputDiagnosticInfoOfLRk(ECO_LANG_C89, pILog, pIMem, pIStr, pILRkAlgorithm);
    }

    /* Отображение правил лексического разбора на правила синтаксического разбора для C89 */
    //pIC89Parser->RuleMapping(pIC89Parser, identifier);
    //pIC89Parser->RuleMapping(pIC89Parser, keyword);
    //pIC89Parser->RuleMapping(pIC89Parser, constant);
    //pIC89Parser->RuleMapping(pIC89Parser, string-literal);
    //pIC89Parser->RuleMapping(pIC89Parser, punctuator);

    /* Получение интерфейса синтаксического разбора согласно заданным правилам для Objective C */
    //pIObjCParser = pISyntax->get_Parser(pISyntax, pIObjCGrammarSyn, 0);

    /* Получение интерфейса по работе с генератором кода */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoToolchainCodeGenerator1, 0, &IID_IEcoToolchainCodeGenerator1, (void**) &pICodeGen);
    /* Проверка */
    if (result != 0 || pICodeGen == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация архитектуры для генерации кода */

    /* Регистрируем эмитер для архитектуры I80686 */
    pICodeGen->pVTbl->RegisterEmitter(pICodeGen, &CID_EcoToolchainEmitterI80686, ECO_CG_1_AT_I80686);

    ///* Регистрация форматов для генерации */

    ///* Регистрация Relocatable Object Module Formats */
    //pICodeGen->pVTbl->RegisterFileFormat(pICodeGen, &CID_EcoOMF1, "OMF");

    /* Регистрируем формат объектного файла PECOFF */
    pICodeGen->pVTbl->RegisterFileFormat(pICodeGen, &CID_EcoPECOFF1, ECO_CG_1_FT_PECOFF);

    /* Переключение на интерфейс синтаксического разбора для C89 */
    pIParser = pIC89Parser;
    //////////////////////////////////////////////////////////
    //    goto CompleteAST;                                 //
    //////////////////////////////////////////////////////////

    /******************************************************************************************** КОМПИЛЯЦИЯ ********************************************************************************************/

    /* Цикл обработки файлов с исходным кодом */
    for (iSourceIndex = 0; iSourceIndex < pISourceFiles->pVTbl->Count(pISourceFiles); iSourceIndex++) {
        /* Получаем имя файла из списка */
        pszSourceFileName = (char_t*)pISourceFiles->pVTbl->Item(pISourceFiles, iSourceIndex);
        printf("Scan file %i: %s\n", iSourceIndex, pszSourceFileName);
        /* Извлекаем расширение файла из имени */
        pszSourceFileExt = pIStr->pVTbl->SearchLastCharacter(pIStr, pszSourceFileName, '.');
        /* Извлекаем имя без расширения */
        pszSourceName = pIStr->pVTbl->Substring(pIStr, pszSourceFileName, 0, pszSourceFileExt-pszSourceFileName );
        /* Проверяем тип расширения для выбора грамматики лексического анализа */
        if (pIStr->pVTbl->Compare(pIStr, pszSourceFileExt, ".S") == 0 || pIStr->pVTbl->Compare(pIStr, pszSourceFileExt, ".asm") == 0) {
            //        /* Получение интерфейса лексического разбора согласно заданным правилам для ассемблера */
            //        //pIScanner = pILexer->new_FileScanner(pILexer, pIAsmGrammarLex, pszSourceFileName);
            //        pIScanner = pILexer->pVTbl->new_FileScannerByFA(pILexer, pIFA, pszSourceFileName);
            //        /* ИЛИ */
            //        /* Получение интерфейса лексического разбора из буфера памяти согласно заданным правилам для ассемблера */
            //        //pIScanner = pILexer->get_MemoryScannerByBNF(pILexer, pIAsmGrammarLex, inputAsmStream, inputAsmSize);
            //        //pIScanner = pILexer->get_MemoryScannerByFA(pILexer, pIFA, inputAsmStream, inputAsmSize);
            //        /* Вывод диагностической/отладочной информации */
            //        //OutputDiagnosticInfoOfScanner(ECO_LANG_ASM, pILog, pIStr, pIScanner);
            //        /* Переключение на интерфейс обработчика препроцессора для ассемблера */
            //        pIPreProcessing = pIAsmPreprocessor->pVTbl->get_Processing(pIAsmPreprocessor);
            //        /* Переключение на интерфейс синтаксического разбора для ассемблера */
            //        pIParser = pIAsmParser;
            //        iActiveLang = ECO_LANG_ASM;
        }
        else if (pIStr->pVTbl->Compare(pIStr, pszSourceFileExt, ".c") == 0) {
            /* Получение интерфейса лексического разбора согласно заданным правилам для C89 */
            //pIScanner = pILexer->new_FileScannerByBNF(pILexer, pIC89GrammarLex, pszSourceFileName);
            pIScanner = pILexer->pVTbl->new_FileScannerByFA(pILexer, pIFA, pszSourceFileName);
            /* ИЛИ */
            /* Получение интерфейса лексического разбора из буфера памяти согласно заданным правилам для C89 */
            //pIScanner = pILexer->get_MemoryScanner(pILexer, pIC89GrammarLex, inputC89Stream, inputC89Size);
            /* Переключение на интерфейс обработчика препроцессора для C89 */
            /* Вывод диагностической/отладочной информации */
            //OutputDiagnosticInfoOfScanner(ECO_LANG_C89, pILog, pIStr, pIScanner);
            pIPreProcessing = pIC89Preprocessor->pVTbl->get_Processing(pIC89Preprocessor);
            /* Переключение на интерфейс синтаксического разбора для C89 */
            pIParser = pIC89Parser;
            iActiveLang = ECO_LANG_C89;
        }
        else if (pIStr->pVTbl->Compare(pIStr, pszSourceFileExt, ".m") == 0) {
            //        /* Переключение на интерфейс синтаксического разбора для Objective C */
            //        //pIParser = pIObjCParser;
            //        iActiveLang = ECO_LANG_OBJC;
        }
        else {
            /* Вывод об ошибки "Неподдерживаемое расширение файла!" и продолжаем обработку следующих файлов */
            continue;
        }

        /* Основной цикл чтения и обработки входной последовательности */
        do {
            /* Лексический анализ */
            if (pITokenList->pVTbl->Count(pITokenList) == 0) {
                pIToken = pIScanner->pVTbl->Scan(pIScanner);
            }
            else {
                pIToken = (IEcoToolchainLexicalAnalyzer1Token*)pITokenList->pVTbl->Pop(pITokenList);
            }
            /* Вывод диагностической/отладочной информации */
            OutputDiagnosticInfoOfScannerStep(iActiveLang, pILog, pIStr, pIToken);

            /* Если у входного потока отсутствуют токены, то проверяем в стеке предыдужий обработчик входной последовательности */
            if (pIToken == 0) {
                if (pIScannerList->pVTbl->Count(pIScannerList) > 0) {
                    /* Извлекаем из стека предыдущий обработчик */
                    pIScanner->pVTbl->Release(pIScanner);
                    pIScanner = (IEcoToolchainLexicalAnalyzer1Scanner*)pIScannerList->pVTbl->Pop(pIScannerList);
                    /* Возврат на прежний цикл обработки */
                    continue;
                }
                else {
                    /* Иначе переходим к обработке завершающего токена */
                    pIScanner->pVTbl->Release(pIScanner);
                    break;
                }
            }


            /* Препроцессорная обработка */
            pIPreResult = pIPreProcessing->pVTbl->InvokeByToken(pIPreProcessing, pIToken);

            /* Если результатом препроцессорной обработки является отбрасывание токенов входного потока, то токен удаляется */
            if (pIPreResult->pVTbl->get_Type(pIPreResult) == ECO_MACROPROCESSOR_TYPE_DELETITION) {
                /* Вывод информации препроцессорной обработки */
                pILog->pVTbl->Info(pILog, "Preprocessing - token deleted");
                /* Освобождение интерфейсов */
                pIPreResult->pVTbl->Release(pIPreResult);
                pIToken->pVTbl->Release(pIToken);
                /* Переход на начало цикла обработки */
                continue;
            }

            /* Проверка режима обработки макроопределения */
            if (pIPreProcessing->pVTbl->IsExpand(pIPreProcessing) == 1) {
                /* Если результатом препроцессорной обработки является макровызов (the expansion of macro invocations),
                то читаем аргументы макро вызова */
                if (pIPreResult->pVTbl->get_Type(pIPreResult) == ECO_MACROPROCESSOR_TYPE_INVOCATION) {
                    /* Переход на начало цикла обработки */
                    pIPreResult->pVTbl->Release(pIPreResult);
                    pIToken->pVTbl->Release(pIToken);
                    continue;
                }
            }

            /* Если результатом препроцессорной обработки является открытие нового входного потока,
            то заносим текущий обработчик лексического разбора в стек для последующей обработки */
            if (pIPreResult->pVTbl->get_Type(pIPreResult) == ECO_MACROPROCESSOR_TYPE_INVOCATION && pIPreResult->pVTbl->get_Command(pIPreResult) == ECO_MACROPROCESSOR_COMMAND_INCLUDE) {
                pIScannerList->pVTbl->Push(pIScannerList, pIScanner);
                /* Получаем имя файла из списка */
                pIMacroExpTokenList = (IEcoList1*)pIPreResult->pVTbl->get_Object(pIPreResult);
                if (pIMacroExpTokenList != 0) {
                    if (pIMacroExpTokenList->pVTbl->Count(pIMacroExpTokenList) > 0) {
                        pIPreToken = (IEcoToolchainLexicalAnalyzer1Token*)pIMacroExpTokenList->pVTbl->Item(pIMacroExpTokenList, 1);
                        pszSourceFileName = pIPreToken->pVTbl->get_Lexeme(pIPreToken);
                        removeChar(pszSourceFileName, '\"');
                        /* Извлекаем расширение файла из имени */
                        pszSourceFileExt = pIStr->pVTbl->SearchLastCharacter(pIStr, pszSourceFileName, '.');
                        /* Проверяем тип расширения для выбора грамматики лексического анализа */
                        if (pIStr->pVTbl->Compare(pIStr, pszSourceFileExt, ".inc") == 0) {
                            /* Получение интерфейса лексического разбора согласно заданным правилам для ассемблера */
                            pIScanner = pILexer->pVTbl->new_FileScannerByBNF(pILexer, pIAsmGrammarLex, pszSourceFileName);
                        }
                        else if (pIStr->pVTbl->Compare(pIStr, pszSourceFileExt, ".h") == 0) {
                            /* Получение интерфейса лексического разбора согласно заданным правилам для C89 */
                            pszSearchFileName = pIStr->pVTbl->Append(pIStr, pszSearchFileName, "..\\..\\..\\TestFiles\\Windows\\");
                            pszSearchFileName = pIStr->pVTbl->Append(pIStr, pszSearchFileName, pszSourceFileName);
                            pIScanner = pILexer->pVTbl->new_FileScannerByFA(pILexer, pIFA, pszSearchFileName);
                        }
                        else {
                            /* Вывод об ошибки и выход из цикла */
                            break;
                        }
                    }
                    pIMacroExpTokenList = 0;
                }

                /* Проверка интерфейса на случай если файл не был найден */
                if (pIScanner != 0) {
                    /* Переход на новый цикл обработки */
                    continue;
                }
                else {
                    /* Вывод об ошибки и выход из цикла */
                    break;
                }
            }

            /* Если результатом препроцессорной обработки является макрорасширение (macroexpansion) входного потока,
            то возвращается один или несколько токенов исходного языка, как список (IEcoList1*) */
            if (pIPreResult->pVTbl->get_Type(pIPreResult) == ECO_MACROPROCESSOR_TYPE_EXPANSION) {
                pIMacroExpTokenList = (IEcoList1*)pIPreResult->pVTbl->get_Object(pIPreResult);
            }

            if (pIMacroExpTokenList != 0) {
                /* Токены перебираются в обратном порядке и добавляются в стек для последующего парсинга*/
                for (iTokenIndex = pIMacroExpTokenList->pVTbl->Count(pIMacroExpTokenList) - 1; iTokenIndex < pIMacroExpTokenList->pVTbl->Count(pIMacroExpTokenList); iTokenIndex--) {
                    pIToken = (IEcoToolchainLexicalAnalyzer1Token*)pIMacroExpTokenList->pVTbl->Item(pIMacroExpTokenList, iTokenIndex);
                    pITokenList->pVTbl->Push(pITokenList, pIToken);
                }
                pIMacroExpTokenList->pVTbl->Clear(pIMacroExpTokenList);
                pIMacroExpTokenList->pVTbl->Release(pIMacroExpTokenList);
                pIMacroExpTokenList = 0;
                //for (iTokenIndex = 0; iTokenIndex < pIMacroExpTokenList->pVTbl->Count(pIMacroExpTokenList); iTokenIndex++) {
                //    pIToken = (IEcoToolchainLexicalAnalyzer1Token*)pIMacroExpTokenList->pVTbl->Item(pIMacroExpTokenList, iTokenIndex);
                //   /* Синтаксический анализ */
                //   pIAction = pIParser->pVTbl->Parse(pIParser, pIToken);
                //   /* Вывод диагностической/отладочной информации */
                //   OutputDiagnosticInfoOfParserStep(iActiveLang, pILog, pIStr, pIAction);
                //}
            }
            /* Если макро операции не выполнялись, то возвращается входной токен исходного языка, где pIToken == pIPreResult->get_Object(pIPreResult)*/
            else if (pIPreResult->pVTbl->get_Type(pIPreResult) == ECO_MACROPROCESSOR_TYPE_PASS) {
                /* Синтаксический анализ */
                while (1) {
                    pIAction = pIParser->pVTbl->Parse(pIParser, pIToken);
                    OutputDiagnosticInfoOfParserStep(iActiveLang, pILog, pIStr, pIAction);
                    if (pIAction->pVTbl->get_Type(pIAction) != ECO_ACTION_PROCESSING_TYPE_REDUCE) {
                        pIAction->pVTbl->Release(pIAction);
                        break;
                    }
                    pIAction->pVTbl->Release(pIAction);
                }
                pIToken->pVTbl->Release(pIToken);
                /* Вывод диагностической/отладочной информации */
            }

            pIPreResult->pVTbl->Release(pIPreResult);

        } while (1);

CompleteAST:
        /* Получение интерфейса по работе с абстрактным синтаксическим деревом */
        pIAST = pIParser->pVTbl->get_AST(pIParser);
        OutputDiagnosticInfoOfAST(ECO_LANG_C89, pILog, pIMem, pIStr, pIAST);

        ///* Формирование имени объектного файла */
        ////pszObjName = pIStr->Append(pIStr, pszSourceFileExt-pszSourceFileName, ".obj");
        ////pszObjName = "..\\..\\..\\TestFiles\\IBMPCx86\\test_8086_en.obj";
        //pszObjName = "..\\..\\..\\TestFiles\\Windows\\main.obj";
        ///* Генерация кода для заданной архитектуры и формата объектного файла для связывания */
        ////result = pICodeGen->pVTbl->GenerateToFile(pICodeGen, "I8086", pIAST, "OMF", pszObjName);

        ///* Генерация кода архитектуры I80686 */
        //pICodeGen->pVTbl->Generate(pICodeGen, pIAST, ECO_CG_1_AT_I80686, 0, &pIEmitter);

        ///* Запись кода в объектный файл формата PECOFF */
        //pICodeGen->pVTbl->WriteObjectFile(pICodeGen, pIEmitter, ECO_CG_1_FT_PECOFF, 0, pszObjName);

        ////if (result != 0) {
        //    /* Вывод об ошибки и выход из цикла */
        ////    break;
        ////}
        ///* Добавляем объектный файл в список связывания */
        //pIObjFiles->pVTbl->Add(pIObjFiles, pszObjName);
        pIPreProcessing->pVTbl->Release(pIPreProcessing);
        pIStr->pVTbl->Free(pIStr, pszSourceName);
    }

    /******************************************************************************************** СВЯЗЫВАНИЕ ********************************************************************************************/

    ///* Получение интерфейса по работе со связыванием объектного кода */
    //result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoToolchainLinker1, 0, &IID_IEcoToolchainLinker1, (void**) &pILinker);
    ///* Проверка */
    //if (result != 0 || pILinker == 0) {
    //    /* Освобождение в случае ошибки */
    //    goto Release;
    //}

    ///* Регистрация форматов для связывания */

    /////* Регистрация Relocatable Object Module Formats */
    ////pILinker->pVTbl->RegisterFileFormat(pILinker, &CID_EcoOMF1, "OMF");

    ///* Регистрация Microsoft Portable Executable and Common Object File Format */
    //pILinker->pVTbl->RegisterFileFormat(pILinker, &CID_EcoPECOFF1, ECO_L_1_FT_PECOFF);

    /////* Регистрация Hexadecimal Object File Format */
    //////pILinker->RegisterFileFormat(pILinker, &CID_EcoHOFF1, "HOFF");

    /////* Регистрация Executable and Linkable Format */
    //////pILinker->RegisterFileFormat(pILinker, &CID_EcoELF1, "ELF");

    ///* Связывание */
    //pILog->pVTbl->Info(pILog, "Linker - create EXE file for Windows platform");

    //pILinker->pVTbl->LinkToFile(pILinker, ECO_L_1_FT_PECOFF, 0, pIObjFiles, 0, ECO_L_1_FT_PECOFF, "..\\..\\..\\TestFiles\\Windows\\HelloWorld.exe");
    //////pILinker->LinkToFile(pILinker, "OMF", pIObjFiles, "BIN", "out.bin");
    //////pILinker->pVTbl->LinkToFile(pILinker, "OMF", pIObjFiles, "BIN", "..\\..\\..\\TestFiles\\IBMPCx86\\kernel.img");
    /////* ИЛИ */
    //////pILinker->LinkToFile(pILinker, "OMF", pIObjFiles, "HOFF", "out.hex");

    /////* Для проверки необходимо перейти в папку ..\TestFiles\IBMPCx86 и запустить run.bat */

Release:

    /* Освобождение интерфейса код-генератора */
    if (pICodeGen != 0) {
        pICodeGen->pVTbl->Release(pICodeGen);
    }

    /* Освобождение интерфейса парсера */
    if (pILRkAlgorithm != 0) {
        pILRkAlgorithm->pVTbl->Release(pILRkAlgorithm);
    }
    if (pIC89Parser != 0) {
        pIC89Parser->pVTbl->Release(pIC89Parser);
    }

    /* Освобождение интерфейса для работы с грамматикой С89 */
    if (pIC89GrammarSyn != 0) {
        pIC89GrammarSyn->pVTbl->Release(pIC89GrammarSyn);
    }

    /* Освобождение интерфейся для работы с синтаксическим анализатором */
    if (pISyntax != 0) {
        pISyntax->pVTbl->Release(pISyntax);
    }

    /* Получение интерфейса для работы с препроцессингом */
    if (pIC89Preprocessor != 0) {
        pIC89Preprocessor->pVTbl->Release(pIC89Preprocessor);
    }

    /* Освобождение интерфейса для работы с лексическим анализатором */
    if (pILexer != 0) {
        pILexer->pVTbl->Release(pILexer);
    }

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение интерфейса конечного автомата */
    if (pIFA != 0) {
        pIFA->pVTbl->Release(pIFA);
    }

    /* интерфейса по работе с грамматикой лексического разбора C89 */
    if (pIC89GrammarLex != 0) {
        pIC89GrammarLex->pVTbl->Release(pIC89GrammarLex);
    }

    /* Освобождение интерфейса по работе со списком  для объектных файлов */
    if (pIObjFiles != 0) {
        pIObjFiles->pVTbl->Release(pIObjFiles);
    }

    /* Освобождение интерфейса по работе со списком исходных файлов */
    if (pISourceFiles != 0) {
        pISourceFiles->pVTbl->Clear(pISourceFiles);
        pISourceFiles->pVTbl->Release(pISourceFiles);
    }

    /* Освобождение интерфейса со списком токенов */
    if (pITokenList != 0) {
        pITokenList->pVTbl->Clear(pITokenList);
        pITokenList->pVTbl->Release(pITokenList);
    }

    /* Освобождение интерфейса по работе со списком сканеров */
    if (pIScannerList != 0) {
        pIScannerList->pVTbl->Clear(pIScannerList);
        pIScannerList->pVTbl->Release(pIScannerList);
    }

    /* Освобождение интерфейса для работы с файлами */
    if (pIFileManager != 0) {
        pIFileManager->pVTbl->Release(pIFileManager);
    }

    /* Освобождение интерфейса для работы с конечным автоматом */
    if (pIFSM != 0) {
        pIFSM->pVTbl->Release(pIFSM);
    }

    /* Освобождение интерфейса для работы с журналом*/
    if (pILog != 0) {
        pILog->pVTbl->Release(pILog);
    }

    /* Освобождение интерфейса для работы со строкой */
    if (pIStr != 0) {
        pIStr->pVTbl->Release(pIStr);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}
