/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoOutputDiagnostic
 * </сводка>
 *
 * <описание>
 *   Данный файл реализует вывод диагностичекской/отладочной информации
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "EcoOutputDiagnostic.h"
#include "IEcoData1.h"
#include "IEcoTree1.h"
#include "IEcoMap1.h"
#include "IEcoBase1.h"
#include <stdio.h>

/*
 *
 * <сводка>
 *   Функция OutputDiagnosticInfoOfBNF
 * </сводка>
 *
 * <описание>
 *   Функция OutputDiagnosticInfoOfBNF - Вывод диагностической информации грамматики
 * </описание>
 *
 */
bool_t OutputDiagnosticInfoOfBNF(/* in */ uint16_t langId, /* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoToolchainBNF1* pGrammar) {
    bool_t bResult = 0;
    IEcoToolchainBNF1Rule* pIRule = 0;
    IEcoToolchainBNF1Element* pIElement = 0;
    IEcoList1* pIAlphabet = 0;
    IEcoList1* pIRules = 0;
    IEcoList1* pIRuleSet = 0;
    IEcoList1* pIElements = 0;
    char_t* word = 0;
    char_t* Rule = 0;
    uint32_t index = 0;
    uint32_t indexSet = 0;
    uint32_t indexElement = 0;

    if (pGrammar != 0) {
        if (langId == ECO_LANG_ASM) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** ASSEMBLER GRAMMAR ******************************");
        }
        else if (langId == ECO_LANG_C89) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** C89 GRAMMAR ******************************");
        }
        else if (langId == ECO_LANG_OBJC) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** OBJECTIVE C GRAMMAR ******************************");
        }
        pILog->pVTbl->InfoFormat(pILog, "Alphabet :");
        pIAlphabet = pGrammar->pVTbl->get_Alphabet(pGrammar);
        for (index = 0; index < pIAlphabet->pVTbl->Count(pIAlphabet); index++) {
            word = (char_t*)pIAlphabet->pVTbl->Item(pIAlphabet, index);
            pILog->pVTbl->InfoFormat(pILog, "%i %s,", index, word);
        }
        pILog->pVTbl->InfoFormat(pILog, "NonTerminal :");
        pIAlphabet = pGrammar->pVTbl->get_NonTerminalAlphabet(pGrammar);
        for (index = 0; index < pIAlphabet->pVTbl->Count(pIAlphabet); index++) {
            word = (char_t*)pIAlphabet->pVTbl->Item(pIAlphabet, index);
            pILog->pVTbl->InfoFormat(pILog, "%i %s,", index, word);
        }
        pILog->pVTbl->InfoFormat(pILog, "Terminal :");
        pIAlphabet = pGrammar->pVTbl->get_TerminalAlphabet(pGrammar);
        for (index = 0; index < pIAlphabet->pVTbl->Count(pIAlphabet); index++) {
            word = (char_t*)pIAlphabet->pVTbl->Item(pIAlphabet, index);
            pILog->pVTbl->InfoFormat(pILog, "%i %s,", index, word);
        }

        /* Вывод правил */
        pIRules = pGrammar->pVTbl->get_RuleList(pGrammar);
        for (index = 0; index < pIRules->pVTbl->Count(pIRules); index++) {
            pIRule = (IEcoToolchainBNF1Rule*)pIRules->pVTbl->Item(pIRules, index);
            Rule = pIStr->pVTbl->Append(pIStr, Rule, (char_t *)pIRule->pVTbl->get_Name(pIRule));
            pIRuleSet = pIRule->pVTbl->get_RuleSet(pIRule);
            for (indexSet = 0; indexSet < pIRuleSet->pVTbl->Count(pIRuleSet); indexSet++) {
                pIElements = (IEcoList1*)pIRuleSet->pVTbl->Item(pIRuleSet, indexSet);
                if (indexSet == 0) {
                    Rule = pIStr->pVTbl->Append(pIStr, Rule, ":\r\n\t");
                }
                else {
                    Rule = pIStr->pVTbl->Append(pIStr, Rule, "\r\n\t");
                }
                for (indexElement = 0; indexElement < pIElements->pVTbl->Count(pIElements); indexElement++) {
                    pIElement = (IEcoToolchainBNF1Element*)pIElements->pVTbl->Item(pIElements, indexElement);
                    if (pIElement->pVTbl->IsOptional(pIElement)) {
                        Rule = pIStr->pVTbl->Append(pIStr, Rule, "[");
                    }
                    Rule = pIStr->pVTbl->Append(pIStr, Rule, (char_t *)pIElement->pVTbl->get_Name(pIElement));
                    if (pIElement->pVTbl->IsOptional(pIElement)) {
                        Rule = pIStr->pVTbl->Append(pIStr, Rule, "]");
                    }
                    Rule = pIStr->pVTbl->Append(pIStr, Rule, " ");
                }
            }
            pILog->pVTbl->InfoFormat(pILog, "Rule [%d]\r\n%s", pIRule->pVTbl->get_Id(pIRule), Rule);
            pIStr->pVTbl->Free(pIStr, Rule);
            Rule = 0;
        }
        bResult = 1;
    }
    return bResult;
}

/*
 *
 * <сводка>
 *   Функция OutputDiagnosticInfoOfScanner
 * </сводка>
 *
 * <описание>
 *   Функция OutputDiagnosticInfoOfScanner - Вывод диагностической информации лексического анализа
 * </описание>
 *
 */
bool_t OutputDiagnosticInfoOfScanner(/* in */ uint16_t langId, /* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoToolchainLexicalAnalyzer1Scanner* pIScanner) {
    bool_t bResult = 0;
    IEcoFSM1StateMachine* pIStateMachine = 0;
    IEcoFSM1State* pIState = 0;
    IEcoFSM1State* pIStateTarget = 0;
    IEcoFSM1Transition* pITransition = 0;
    IEcoList1* pIEvents = 0;
    IEcoList1* pITransitions = 0;
    IEcoFSM1Event* pIEvent = 0;
    IEcoFSM1Event* pITempEvent = 0;
    IEcoFSM1State* pISourceState = 0;
    uint32_t indexEvent = 0;
    uint32_t indexTransition = 0;
    IEcoData1Table* pITransitionTable = 0;
    IEcoList1* pIColumns = 0;
    IEcoList1* pIRows = 0;
    IEcoData1Column* pIColumn = 0;
    IEcoData1Row* pIRow = 0;
    uint32_t index = 0;
    uint32_t indexColumn = 0;
    uint32_t indexRow = 0;
    uint32_t countAlign = 0;
    char_t* Line = 0;
    char_t* Headers = 0;

    if (pIScanner != 0) {
        if (langId == ECO_LANG_ASM) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** ASSEMBLER SCANNER ******************************");
        }
        else if (langId == ECO_LANG_C89) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** C89 SCANNER ******************************");
        }
        else if (langId == ECO_LANG_OBJC) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** OBJECTIVE C SCANNER ******************************");
        }

        /* Получение конечного автомата */
        pIStateMachine = pIScanner->pVTbl->get_FSM(pIScanner);
        /* Вывод конечного автомата */
        pILog->pVTbl->InfoFormat(pILog, "StateMachine [%s]", pIStateMachine->pVTbl->get_Name(pIStateMachine));

        /* Вывод управляющей таблицы */
        pITransitionTable = pIStateMachine->pVTbl->get_TransitionTable(pIStateMachine);
        if (pITransitionTable != 0) {
            pIColumns = pITransitionTable->pVTbl->get_Columns(pITransitionTable);
            pILog->pVTbl->InfoFormat(pILog, "Table [%s]", pITransitionTable->pVTbl->get_Name(pITransitionTable));
            Line = pIStr->pVTbl->Append(pIStr, Line, "+-------+");
            Headers = pIStr->pVTbl->Append(pIStr, Headers, "| S \\ E |");
            for (indexColumn = 0; indexColumn < pIColumns->pVTbl->Count(pIColumns); indexColumn++) {
                pIColumn = (IEcoData1Column*)pIColumns->pVTbl->Item(pIColumns, indexColumn);
                Line = pIStr->pVTbl->Append(pIStr, Line, "--");
                Headers = pIStr->pVTbl->Append(pIStr, Headers, "  ");
                Headers = pIStr->pVTbl->Append(pIStr, Headers, pIColumn->pVTbl->get_Name(pIColumn));
                countAlign = pIStr->pVTbl->RetrieveSize(pIStr, pIColumn->pVTbl->get_Name(pIColumn));
                if (countAlign == 2) {
                    Headers = pIStr->pVTbl->Append(pIStr, Headers, " |");
                }
                else {
                    Headers = pIStr->pVTbl->Append(pIStr, Headers, "  |");
                }
                Line = pIStr->pVTbl->Append(pIStr, Line, "---+");
            }
            pILog->pVTbl->InfoFormat(pILog, "%s", Line);
            pILog->pVTbl->InfoFormat(pILog, "%s", Headers);
            pILog->pVTbl->InfoFormat(pILog, "%s", Line);
            pIStr->pVTbl->Free(pIStr, Headers);
            Headers = 0;

            pIRows = pITransitionTable->pVTbl->get_Rows(pITransitionTable);
            for (indexRow = 0; indexRow < pIRows->pVTbl->Count(pIRows)-1; indexRow++) {
                Headers = pIStr->pVTbl->Append(pIStr, Headers, "|");
                pIRow = (IEcoData1Row*)pIRows->pVTbl->Item(pIRows, indexRow);
                Headers = pIStr->pVTbl->Append(pIStr, Headers, "   ");
                Headers = pIStr->pVTbl->Append(pIStr, Headers, pIStr->pVTbl->ConvertIntToString(pIStr, indexRow));
                countAlign = pIStr->pVTbl->RetrieveSize(pIStr, Headers);
                if (countAlign == 6) {
                    Headers = pIStr->pVTbl->Append(pIStr, Headers, "  |");
                }
                else {
                    Headers = pIStr->pVTbl->Append(pIStr, Headers, "   |");
                }
                for (indexColumn = 0; indexColumn < pIColumns->pVTbl->Count(pIColumns); indexColumn++) {
                    if (pIRow->pVTbl->IsNullByIndex(pIRow, indexColumn)) {
                        Headers = pIStr->pVTbl->Append(pIStr, Headers, "     |");
                    } else {
                        Headers = pIStr->pVTbl->Append(pIStr, Headers, " ");
                        Headers = pIStr->pVTbl->Append(pIStr, Headers, (char_t*)pIRow->pVTbl->get_ItemByIndex(pIRow, indexColumn));
                        Headers = pIStr->pVTbl->Append(pIStr, Headers, " |");
                    }
                }
                pILog->pVTbl->InfoFormat(pILog, "%s", Headers);
                pILog->pVTbl->InfoFormat(pILog, "%s", Line);
                pIStr->pVTbl->Free(pIStr, Headers);
                Headers = 0;
            }
            pIStr->pVTbl->Free(pIStr, Line);
            Line = 0;
        }

    }
    return bResult;
}

/*
 *
 * <сводка>
 *   Функция OutputDiagnosticInfoOfScannerStep
 * </сводка>
 *
 * <описание>
 *   Функция OutputDiagnosticInfoOfScannerStep - Вывод диагностической информации шага лексического анализа
 * </описание>
 *
 */
bool_t OutputDiagnosticInfoOfScannerStep(/* in */ uint16_t langId, /* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoToolchainLexicalAnalyzer1Token* pIToken) {
    bool_t bResult = 0;
    if (pIToken != 0) {
        if (langId == ECO_LANG_ASM) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** ASSEMBLER SCANNER STEP ******************************");
        }
        else if (langId == ECO_LANG_C89) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** C89 SCANNER STEP ******************************");
        }
        else if (langId == ECO_LANG_OBJC) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** OBJECTIVE C SCANNER STEP ******************************");
        }
        pILog->pVTbl->InfoFormat(pILog, "Token Type = %d, Lexem = %s, Description = %s", pIToken->pVTbl->get_Type(pIToken), pIToken->pVTbl->get_Lexeme(pIToken), pIToken->pVTbl->get_Description(pIToken));
        pILog->pVTbl->InfoFormat(pILog, "Token Line = %d, Column = %d", pIToken->pVTbl->get_Line(pIToken), pIToken->pVTbl->get_Column(pIToken));
        pILog->pVTbl->InfoFormat(pILog, "Token Source = %s, Position = %d, Length = %d", pIToken->pVTbl->get_Source(pIToken), pIToken->pVTbl->get_Position(pIToken), pIToken->pVTbl->get_Length(pIToken));
    }
    return bResult;
}

/*
 *
 * <сводка>
 *   Функция OutputDiagnosticInfoOfParserStep
 * </сводка>
 *
 * <описание>
 *   Функция OutputDiagnosticInfoOfParserStep - Вывод диагностической информации шага синтаксического анализа
 * </описание>
 *
 */
bool_t OutputDiagnosticInfoOfParserStep(/* in */ uint16_t langId, /* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoToolchainParser1Action* pIAction) {
    
    bool_t bResult = 0;
    if (pIAction != 0) {
        if (langId == ECO_LANG_ASM) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** ASSEMBLER PARSER STEP ******************************");
        }
        else if (langId == ECO_LANG_C89) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** C89 PARSER STEP ******************************");
        }
        else if (langId == ECO_LANG_OBJC) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** OBJECTIVE C PARSER STEP ******************************");
        }
        if (pIAction != 0) {
            pILog->pVTbl->InfoFormat(pILog, "Action Description = %s", pIAction->pVTbl->get_Description(pIAction));
        }
        else {
            pILog->pVTbl->InfoFormat(pILog, "Action Description = (null)");
        }
    }
    return bResult;
}

/*
 *
 * <сводка>
 *   Функция OutputDiagnosticInfoOfFA
 * </сводка>
 *
 * <описание>
 *   Функция OutputDiagnosticInfoOfFA - Вывод диагностической информации конечного автомата
 * </описание>
 *
 */
bool_t OutputDiagnosticInfoOfFA(/* in */ uint16_t langId, /* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoFSM1StateMachine* pIFA) {
    bool_t bResult = 0;
    IEcoFSM1Transition* pITransition = 0;
    IEcoFSM1State* pISource = 0;
    IEcoFSM1State* pITarget = 0;
    IEcoFSM1Event* pIEvent = 0;
    IEcoList1* pITransitions = 0;
    IEcoList1* pIColumns = 0;
    IEcoList1* pIRows = 0;
    uint32_t index = 0;
    char_t* Line = 0;
    char_t* subLine = 0;
    IEcoFSM1State* pIState = 0;
    IEcoFSM1State* pIStateTarget = 0;
    IEcoList1* pIEvents = 0;
    IEcoFSM1Event* pITempEvent = 0;
    IEcoFSM1State* pISourceState = 0;
    uint32_t indexEvent = 0;
    uint32_t indexTransition = 0;
    IEcoData1Table* pITransitionTable = 0;
    IEcoData1Column* pIColumn = 0;
    IEcoData1Row* pIRow = 0;
    uint32_t indexColumn = 0;
    uint32_t indexRow = 0;
    uint32_t countAlign = 0;
    char_t* Headers = 0;

    uint32_t i = 0;
    IEcoFSM1Transition* pITransition2 = 0;
    IEcoFSM1State* source1 = 0;
    IEcoFSM1State* source2 = 0;
    IEcoFSM1Event* event1 = 0;
    IEcoFSM1Event* event2 = 0;
    IEcoFSM1State* target1 = 0;
    IEcoFSM1State* target2 = 0;

    if (pIFA != 0) {
        if (langId == ECO_LANG_ASM) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** ASSEMBLER GRAMMAR ******************************");
        }
        else if (langId == ECO_LANG_C89) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** C89 GRAMMAR ******************************");
        }
        else if (langId == ECO_LANG_OBJC) {
            pILog->pVTbl->InfoFormat(pILog, "****************************** OBJECTIVE C GRAMMAR ******************************");
        }
        pILog->pVTbl->InfoFormat(pILog, "Finite Automata Name = %s", pIFA->pVTbl->get_Name(pIFA));
        /* Вывод переходов конечного автомата */
        pILog->pVTbl->Info(pILog, "Transitions :");
        pITransitions = pIFA->pVTbl->get_Transitions(pIFA);

        for (index = 0; index < pITransitions->pVTbl->Count(pITransitions); ++index) {
            pITransition = pITransitions->pVTbl->Item(pITransitions, index);
            source1 = pITransition->pVTbl->get_Source(pITransition);
            event1 = pITransition->pVTbl->get_Event(pITransition);
            target1 = pITransition->pVTbl->get_Target(pITransition);
            for (i = 0; i < index; ++i) {
                pITransition2 = pITransitions->pVTbl->Item(pITransitions, i);
                source2 = pITransition2->pVTbl->get_Source(pITransition2);
                event2 = pITransition2->pVTbl->get_Event(pITransition2);
                target2 = pITransition2->pVTbl->get_Target(pITransition2);
                if (pIStr->pVTbl->Compare(pIStr, source1->pVTbl->get_Name(source1), source2->pVTbl->get_Name(source2)) == 0 &&
                    pIStr->pVTbl->Compare(pIStr, event1->pVTbl->get_Name(event1), event2->pVTbl->get_Name(event2)) == 0) {
                    printf("WARNING! [%i][%i]\n", index, i);
                    printf("\t%s -%s-> %s\n", source1->pVTbl->get_Name(source1), event1->pVTbl->get_Name(event1), target1->pVTbl->get_Name(target1));
                    printf("\t%s -%s-> %s\n", source2->pVTbl->get_Name(source2), event2->pVTbl->get_Name(event2), target2->pVTbl->get_Name(target2));
                }
            }
        }


        for(index = 0; index < pITransitions->pVTbl->Count(pITransitions); index++) {
            pITransition = (IEcoFSM1Transition*)pITransitions->pVTbl->Item(pITransitions, index);
            pIEvent = pITransition->pVTbl->get_Event(pITransition);
            pISource = pITransition->pVTbl->get_Source(pITransition);
            pITarget = pITransition->pVTbl->get_Target(pITransition);
            Line = 0;
            Line = pIStr->pVTbl->Append(pIStr, Line, "Transition - [");
            subLine = pIStr->pVTbl->ConvertIntToString(pIStr, pITransition->pVTbl->get_Id(pITransition));
            Line = pIStr->pVTbl->Append(pIStr, Line, subLine);
            pIStr->pVTbl->Free(pIStr, subLine);
            Line = pIStr->pVTbl->Append(pIStr, Line, "]: ");
            if (pISource->pVTbl->IsInitial(pISource)) {
                Line = pIStr->pVTbl->Append(pIStr, Line, "->");
            }
            if (pISource->pVTbl->IsFinal(pISource)) {
                Line = pIStr->pVTbl->Append(pIStr, Line, "(");
            }
            Line = pIStr->pVTbl->Append(pIStr, Line, "(");
            Line = pIStr->pVTbl->Append(pIStr, Line, pISource->pVTbl->get_Name(pISource));
            if (pISource->pVTbl->IsFinal(pISource)) {
                Line = pIStr->pVTbl->Append(pIStr, Line, ")");
            }
            Line = pIStr->pVTbl->Append(pIStr, Line, ") -- ");
            Line = pIStr->pVTbl->Append(pIStr, Line, pIEvent->pVTbl->get_Name(pIEvent));
            Line = pIStr->pVTbl->Append(pIStr, Line, " --> (");
            if (pITarget->pVTbl->IsFinal(pITarget)) {
                Line = pIStr->pVTbl->Append(pIStr, Line, "(");
            }
            Line = pIStr->pVTbl->Append(pIStr, Line, pITarget->pVTbl->get_Name(pITarget));
            Line = pIStr->pVTbl->Append(pIStr, Line, ")");
            if (pITarget->pVTbl->IsFinal(pITarget)) {
                Line = pIStr->pVTbl->Append(pIStr, Line, ")  -  ");
                Line = pIStr->pVTbl->Append(pIStr, Line, (char_t*)pITarget->pVTbl->get_Parameter(pITarget));
            }

            pILog->pVTbl->Info(pILog, Line);
            pIStr->pVTbl->Free(pIStr, Line);
            Line = 0;
        }

        /* Вывод управляющей таблицы */
        // TODO: Проблемы с памятью! Автомат недетерминированный! 
        //pITransitionTable = pIFA->pVTbl->get_TransitionTable(pIFA);
        //if (pITransitionTable != 0) {
        //    Headers = 0;
        //    Line = 0;
        //    pIColumns = pITransitionTable->pVTbl->get_Columns(pITransitionTable);
        //    pIRows = pITransitionTable->pVTbl->get_Rows(pITransitionTable);
        //    pILog->pVTbl->InfoFormat(pILog, "Table [%s]", pITransitionTable->pVTbl->get_Name(pITransitionTable));
        //    Line = pIStr->pVTbl->Append(pIStr, Line, "+--------+");
        //    Headers = pIStr->pVTbl->Append(pIStr, Headers, "| S \\ E  |");
        //    for (indexColumn = 0; indexColumn < pIColumns->pVTbl->Count(pIColumns); indexColumn++) {
        //        pIColumn = (IEcoData1Column*)pIColumns->pVTbl->Item(pIColumns, indexColumn);
        //        Line = pIStr->pVTbl->Append(pIStr, Line, "--");
        //        Headers = pIStr->pVTbl->Append(pIStr, Headers, "  ");
        //        Headers = pIStr->pVTbl->Append(pIStr, Headers, pIColumn->pVTbl->get_Name(pIColumn));
        //        countAlign = pIStr->pVTbl->RetrieveSize(pIStr, pIColumn->pVTbl->get_Name(pIColumn));
        //        if (countAlign == 3) {
        //            Headers = pIStr->pVTbl->Append(pIStr, Headers, " |");
        //        }
        //        else if (countAlign == 2) {
        //            Headers = pIStr->pVTbl->Append(pIStr, Headers, "  |");
        //        }
        //        else {
        //            Headers = pIStr->pVTbl->Append(pIStr, Headers, "   |");
        //        }
        //        Line = pIStr->pVTbl->Append(pIStr, Line, "----+");
        //    }
        //    pILog->pVTbl->InfoFormat(pILog, "%s", Line);
        //    pILog->pVTbl->InfoFormat(pILog, "%s", Headers);
        //    pILog->pVTbl->InfoFormat(pILog, "%s", Line);
        //    pIStr->pVTbl->Free(pIStr, Headers);
        //    Headers = 0;


        //    for (indexRow = 0; indexRow < pIRows->pVTbl->Count(pIRows); indexRow++) {
        //        Headers = pIStr->pVTbl->Append(pIStr, Headers, "|");
        //        pIRow = (IEcoData1Row*)pIRows->pVTbl->Item(pIRows, indexRow);
        //        Headers = pIStr->pVTbl->Append(pIStr, Headers, "   ");
        //        Headers = pIStr->pVTbl->Append(pIStr, Headers, pIStr->pVTbl->ConvertIntToString(pIStr, indexRow));
        //        countAlign = pIStr->pVTbl->RetrieveSize(pIStr, Headers);
        //        if (countAlign == 7) {
        //            Headers = pIStr->pVTbl->Append(pIStr, Headers, "  |");
        //        }
        //        else if (countAlign == 6) {
        //            Headers = pIStr->pVTbl->Append(pIStr, Headers, "   |");
        //        }
        //        else {
        //            Headers = pIStr->pVTbl->Append(pIStr, Headers, "    |");
        //        }
        //        for (indexColumn = 0; indexColumn < pIColumns->pVTbl->Count(pIColumns); indexColumn++) {
        //            if (pIRow->pVTbl->IsNullByIndex(pIRow, indexColumn)) {
        //                Headers = pIStr->pVTbl->Append(pIStr, Headers, "      |");
        //            } else {
        //                Headers = pIStr->pVTbl->Append(pIStr, Headers, " ");
        //                Headers = pIStr->pVTbl->Append(pIStr, Headers, (char_t*)pIRow->pVTbl->get_ItemByIndex(pIRow, indexColumn));
        //                Headers = pIStr->pVTbl->Append(pIStr, Headers, " |");
        //            }
        //        }
        //        pILog->pVTbl->InfoFormat(pILog, "%s", Headers);
        //        pILog->pVTbl->InfoFormat(pILog, "%s", Line);
        //        pIStr->pVTbl->Free(pIStr, Headers);
        //        Headers = 0;
        //    }
        //    pIStr->pVTbl->Free(pIStr, Line);
        //    Line = 0;
        //}

    }
    return bResult;
}

/*
 *
 * <сводка>
 *   Функция OutputDiagnosticInfoOfLRk
 * </сводка>
 *
 * <описание>
 *   Функция OutputDiagnosticInfoOfLRk - Вывод диагностической информации алгоритма синтаксического разбора
 * </описание>
 *
 */
bool_t OutputDiagnosticInfoOfLRk(/* in */ uint16_t langId, /* in */ IEcoLog1* pILog, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoString1* pIStr, /* in */ IEcoToolchainParser1LRk* pILRk) {
    bool_t bResult = 0;
    IEcoToolchainParser1LRkItem* pIItem = 0;
    IEcoFSM1StateMachine* pIStateMashine = 0;
    IEcoData1Table* pIActionTable = 0;
    IEcoData1Column* pIColumn = 0;
    IEcoData1Row* pIRow = 0;
    IEcoFSM1State* pIState = 0;
    IEcoToolchainParser1Action* pIAction = 0;
    IEcoList1* pIItemSets = 0;
    IEcoList1* pIColumns = 0;
    IEcoList1* pIRows = 0;
    IEcoList1* pIStates = 0;
    IEcoMap1* pIFirst = 0;
    IEcoMap1* pIFollow = 0;
    IEcoSet1* pISet = 0;
    IEcoSet1* pIItems = 0;
    IEcoMap1Iterator* pIMapIter = 0;
    IEcoSet1Iterator* pISetIter = 0;
    char_t* elemName = 0;
    char_t* ruleStr = 0;
    uint32_t* columnSizes = 0;
    uint32_t actionDescSize = 0;
    uint32_t i = 0, j = 0;
    char_t* appendStr = 0;
    char_t* rowStr = 0;
    char_t* line = 0;

    if (langId == ECO_LANG_ASM) {
        pILog->pVTbl->InfoFormat(pILog, "****************************** ASSEMBLER GRAMMAR ******************************");
    }
    else if (langId == ECO_LANG_C89) {
        pILog->pVTbl->InfoFormat(pILog, "****************************** C89 GRAMMAR ******************************");
    }
    else if (langId == ECO_LANG_OBJC) {
        pILog->pVTbl->InfoFormat(pILog, "****************************** OBJECTIVE C GRAMMAR ******************************");
    }

    pILog->pVTbl->InfoFormat(pILog, "%s", "<----------FIRST---------->");
    pIFirst = pILRk->pVTbl->get_First(pILRk);
    for (pIMapIter = pIFirst->pVTbl->Get_IterBegin(pIFirst); pIMapIter->pVTbl->Get_Key(pIMapIter) != 0; pIMapIter->pVTbl->GoToNext(pIMapIter)) {
        elemName = (char_t*)pIMapIter->pVTbl->Get_Key(pIMapIter);
        pISet = (IEcoSet1*)pIMapIter->pVTbl->Get_Value(pIMapIter);
        for (pISetIter = pISet->pVTbl->Get_IterBegin(pISet); pISetIter->pVTbl->Get_Value(pISetIter); pISetIter->pVTbl->GoToNext(pISetIter)) {
            ruleStr = pIStr->pVTbl->Append(pIStr, ruleStr, " ");
            ruleStr = pIStr->pVTbl->Append(pIStr, ruleStr, (char_t*)pISetIter->pVTbl->Get_Value(pISetIter));
        }
        pISetIter->pVTbl->Release(pISetIter);
        pILog->pVTbl->InfoFormat(pILog, "FIRST[%s]:%s", elemName, ruleStr);
        pIStr->pVTbl->Free(pIStr, ruleStr);
        ruleStr = 0;
    }
    pIMapIter->pVTbl->Release(pIMapIter);

    pILog->pVTbl->InfoFormat(pILog, "%s", "<----------FOLLOW---------->");
    pIFollow = pILRk->pVTbl->get_Follow(pILRk);
    for (pIMapIter = pIFollow->pVTbl->Get_IterBegin(pIFollow); pIMapIter->pVTbl->Get_Key(pIMapIter); pIMapIter->pVTbl->GoToNext(pIMapIter)) {
        elemName = (char_t*)pIMapIter->pVTbl->Get_Key(pIMapIter);
        pISet = (IEcoSet1*)pIMapIter->pVTbl->Get_Value(pIMapIter);
        for (pISetIter = pISet->pVTbl->Get_IterBegin(pISet); pISetIter->pVTbl->Get_Value(pISetIter); pISetIter->pVTbl->GoToNext(pISetIter)) {
            ruleStr = pIStr->pVTbl->Append(pIStr, ruleStr, " ");
            ruleStr = pIStr->pVTbl->Append(pIStr, ruleStr, (char_t*)pISetIter->pVTbl->Get_Value(pISetIter));
        }
        pISetIter->pVTbl->Release(pISetIter);
        pILog->pVTbl->InfoFormat(pILog, "FOLLOW[%s]:%s", elemName, ruleStr);
        pIStr->pVTbl->Free(pIStr, ruleStr);
        ruleStr = 0;
    }
    pIMapIter->pVTbl->Release(pIMapIter);

    pILog->pVTbl->InfoFormat(pILog, "%s", "<----------ITEM_SET---------->");
    pIItemSets = pILRk->pVTbl->get_ItemSets(pILRk);
    for (i = 0; i < pIItemSets->pVTbl->Count(pIItemSets); ++i) {
        pILog->pVTbl->InfoFormat(pILog, "ItemSet[%i]", i);
        pIItems = (IEcoSet1*)pIItemSets->pVTbl->Item(pIItemSets, i);
        for (pISetIter = pIItems->pVTbl->Get_IterBegin(pIItems); pISetIter->pVTbl->Get_Value(pISetIter) != 0; pISetIter->pVTbl->GoToNext(pISetIter)) {
            pIItem = (IEcoToolchainParser1LRkItem*)pISetIter->pVTbl->Get_Value(pISetIter);
            pILog->pVTbl->InfoFormat(pILog, "\t%s", pIItem->pVTbl->get_Description(pIItem));
        }
        pISetIter->pVTbl->Release(pISetIter);
    }

    pILog->pVTbl->InfoFormat(pILog, "%s", "<----------ACTION_TABLE---------->");
    pIStateMashine = pILRk->pVTbl->get_StateMachine(pILRk);
    pIStates = pIStateMashine->pVTbl->get_States(pIStateMashine);
    pIActionTable = pILRk->pVTbl->get_ActionTable(pILRk);
    pIRows = pIActionTable->pVTbl->get_Rows(pIActionTable);
    pIColumns = pIActionTable->pVTbl->get_Columns(pIActionTable);
    columnSizes = pIMem->pVTbl->Alloc(pIMem, pIColumns->pVTbl->Count(pIColumns) * sizeof(int32_t));
    line = pIStr->pVTbl->Append(pIStr, line, "------+");
    for (i = 0; i < pIColumns->pVTbl->Count(pIColumns); ++i) {
        pIColumn = (IEcoData1Column*)pIColumns->pVTbl->Item(pIColumns, i);
        columnSizes[i] = pIStr->pVTbl->RetrieveSize(pIStr, pIColumn->pVTbl->get_Name(pIColumn));
        for (j = 0; j < pIRows->pVTbl->Count(pIRows); ++j) {
            pIRow = (IEcoData1Row*)pIRows->pVTbl->Item(pIRows, j);
            pIAction = (IEcoToolchainParser1Action*)pIRow->pVTbl->get_ItemByIndex(pIRow, i);
            actionDescSize = pIStr->pVTbl->RetrieveSize(pIStr, pIAction->pVTbl->get_Description(pIAction));
            columnSizes[i] = (columnSizes[i] >= actionDescSize) ? columnSizes[i] : actionDescSize;
        }
        appendStr = pIStr->pVTbl->Repeate(pIStr, "-", columnSizes[i] + 2);
        line = pIStr->pVTbl->Append(pIStr, line, appendStr);
        pIStr->pVTbl->Free(pIStr, appendStr);
        appendStr = 0;
        line = pIStr->pVTbl->Append(pIStr, line, "+");
    }

    pILog->pVTbl->InfoFormat(pILog, "Table [%s]", pIActionTable->pVTbl->get_Name(pIActionTable));
    rowStr = pIStr->pVTbl->Append(pIStr, rowStr, "      |");
    for (i = 0; i < pIColumns->pVTbl->Count(pIColumns); ++i) {
        pIColumn = (IEcoData1Column*)pIColumns->pVTbl->Item(pIColumns, i);
        elemName = pIColumn->pVTbl->get_Name(pIColumn);
        rowStr = pIStr->pVTbl->Append(pIStr, rowStr, " ");
        rowStr = pIStr->pVTbl->Append(pIStr, rowStr, elemName);
        appendStr = pIStr->pVTbl->Repeate(pIStr, " ", columnSizes[i] - pIStr->pVTbl->RetrieveSize(pIStr, elemName));
        rowStr = pIStr->pVTbl->Append(pIStr, rowStr, appendStr);
        pIStr->pVTbl->Free(pIStr, appendStr);
        rowStr = pIStr->pVTbl->Append(pIStr, rowStr, " |");
    }
    pILog->pVTbl->Info(pILog, rowStr);
    pILog->pVTbl->Info(pILog, line);
    pIStr->pVTbl->Free(pIStr, rowStr);
    rowStr = 0;

    for (i = 0; i < pIRows->pVTbl->Count(pIRows); ++i) {
        pIRow = (IEcoData1Row*)pIRows->pVTbl->Item(pIRows, i);
        pIState = (IEcoFSM1State*)pIStates->pVTbl->Item(pIStates, i);
        elemName = pIState->pVTbl->get_Name(pIState);
        rowStr = pIStr->pVTbl->Append(pIStr, rowStr, " ");
        rowStr = pIStr->pVTbl->Append(pIStr, rowStr, elemName);
        appendStr = pIStr->pVTbl->Repeate(pIStr, " ", 4 - pIStr->pVTbl->RetrieveSize(pIStr, elemName));
        rowStr = pIStr->pVTbl->Append(pIStr, rowStr, appendStr);
        pIStr->pVTbl->Free(pIStr, appendStr);
        rowStr = pIStr->pVTbl->Append(pIStr, rowStr, " |");
        for (j = 0; j < pIColumns->pVTbl->Count(pIColumns); ++j) {
            pIColumn = (IEcoData1Column*)pIColumns->pVTbl->Item(pIColumns, j);
            pIAction = (IEcoToolchainParser1Action*)pIRow->pVTbl->get_ItemByIndex(pIRow, j);
            if (pIAction->pVTbl->get_Type(pIAction) != ECO_ACTION_PROCESSING_TYPE_ERROR) {
                elemName = pIAction->pVTbl->get_Description(pIAction);
            }
            else {
                elemName = 0;
            }
            if (pIAction->pVTbl->get_Type(pIAction) == ECO_ACTION_PROCESSING_TYPE_CONFLICT) {
                printf("Warning! Found conflict in %i state and '%s' next term: %s\n", i, pIColumn->pVTbl->get_Name(pIColumn), elemName);
            }
            rowStr = pIStr->pVTbl->Append(pIStr, rowStr, " ");
            rowStr = pIStr->pVTbl->Append(pIStr, rowStr, elemName);
            appendStr = pIStr->pVTbl->Repeate(pIStr, " ", columnSizes[j] - pIStr->pVTbl->RetrieveSize(pIStr, elemName));
            rowStr = pIStr->pVTbl->Append(pIStr, rowStr, appendStr);
            pIStr->pVTbl->Free(pIStr, appendStr);
            rowStr = pIStr->pVTbl->Append(pIStr, rowStr, " |");
        }
        pILog->pVTbl->Info(pILog, rowStr);
        pILog->pVTbl->Info(pILog, line);
        pIStr->pVTbl->Free(pIStr, rowStr);
        rowStr = 0;
    }

    pIMem->pVTbl->Free(pIMem, columnSizes);
    pIStr->pVTbl->Free(pIStr, line);

    return bResult;
}

bool_t OutputDiagnosticInfoOfASTNode(/* in */ IEcoLog1* pILog, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoString1* pIStr, /* in */ IEcoTree1Node* pINode, char_t* offset) {
    IEcoTree1Node* pIChildNode = 0;
	IEcoToolchainAST1Scope* pIScope = 0;
    IEcoToolchainAST1GlobalScope* pIGlobalScope = 0;
	IEcoToolchainAST1SyntaxObject* pIObject = 0;
	IEcoToolchainAST1Declaration* pIDeclaration = 0;
	IEcoToolchainAST1StructOrUnionDeclaration* pIStructDeclaration = 0;
	IEcoToolchainAST1StructOrUnionType* pIUndeclaredType = 0;
	IEcoToolchainAST1EnumDeclaration* pIEnumDeclaration = 0;
	IEcoToolchainAST1EnumType* pIUndeclaredEnumType = 0;
    IEcoToolchainAST1FunctionDefinition* pIDefinition = 0;
	IEcoList1* pIDeclarations = 0;
	char_t* description = 0;
    IEcoList1* pIChildren = 0;
    char_t* new_offset = 0;
    uint32_t i = 0;
	int32_t result = 0;

    pILog->pVTbl->InfoFormat(pILog, "%s|_ %s", offset, pINode->pVTbl->get_Name(pINode));

	///* Try to get scope */
	result = pINode->pVTbl->QueryInterface(pINode, &IID_IEcoToolchainAST1Scope, (void**)&pIScope);
	if (result == 0 && pIScope != 0) {
		/* Add declarations */
		pIDeclarations = pIScope->pVTbl->get_Declarations(pIScope);
		for (i = 0; i < pIDeclarations->pVTbl->Count(pIDeclarations); ++i) {
			pIDeclaration = (IEcoToolchainAST1Declaration*)pIDeclarations->pVTbl->Item(pIDeclarations, i);
			description = pIStr->pVTbl->Append(pIStr, description, pIDeclaration->pVTbl->get_IdentifierName(pIDeclaration));
			description = pIStr->pVTbl->Append(pIStr, description, " ");
		}
		pILog->pVTbl->InfoFormat(pILog, "%s|     Declarations: %s", offset, description);
		pIStr->pVTbl->Free(pIStr, description);
		description = 0;
		pIDeclarations->pVTbl->Clear(pIDeclarations);
		pIDeclarations->pVTbl->Release(pIDeclarations);

		/* Add struct or union declarations */
		pIDeclarations = pIScope->pVTbl->get_StructOrUnionDeclarations(pIScope);
		for (i = 0; i < pIDeclarations->pVTbl->Count(pIDeclarations); ++i) {
			pIStructDeclaration = (IEcoToolchainAST1StructOrUnionDeclaration*)pIDeclarations->pVTbl->Item(pIDeclarations, i);
			description = pIStr->pVTbl->Append(pIStr, description, pIStructDeclaration->pVTbl->get_IdentifierName(pIStructDeclaration));
			description = pIStr->pVTbl->Append(pIStr, description, " ");
		}
		pILog->pVTbl->InfoFormat(pILog, "%s|     Struct or union declarations: %s", offset, description);
		pIStr->pVTbl->Free(pIStr, description);
		description = 0;
		pIDeclarations->pVTbl->Clear(pIDeclarations);
		pIDeclarations->pVTbl->Release(pIDeclarations);

		/* Add enum declarations */
		pIDeclarations = pIScope->pVTbl->get_EnumDeclarations(pIScope);
		for (i = 0; i < pIDeclarations->pVTbl->Count(pIDeclarations); ++i) {
			pIEnumDeclaration = (IEcoToolchainAST1EnumDeclaration*)pIDeclarations->pVTbl->Item(pIDeclarations, i);
			description = pIStr->pVTbl->Append(pIStr, description, pIEnumDeclaration->pVTbl->get_IdentifierName(pIEnumDeclaration));
			description = pIStr->pVTbl->Append(pIStr, description, " ");
		}
		pILog->pVTbl->InfoFormat(pILog, "%s|     Enum declarations: %s", offset, description);
		pIStr->pVTbl->Free(pIStr, description);
		description = 0;
		pIDeclarations->pVTbl->Clear(pIDeclarations);
		pIDeclarations->pVTbl->Release(pIDeclarations);

		/* Add undeclared types */
		pIDeclarations = pIScope->pVTbl->get_UndeclaredTypes(pIScope);
		for (i = 0; i < pIDeclarations->pVTbl->Count(pIDeclarations); ++i) {
			pIUndeclaredType = (IEcoToolchainAST1StructOrUnionType*)pIDeclarations->pVTbl->Item(pIDeclarations, i);
			description = pIStr ->pVTbl->Append(pIStr, description, pIUndeclaredType->pVTbl->get_TypeName(pIUndeclaredType));
			description = pIStr->pVTbl->Append(pIStr, description, " ");
		}
		pILog->pVTbl->InfoFormat(pILog, "%s|     Undeclared types: %s", offset, description);
		pIStr->pVTbl->Free(pIStr, description);
		description = 0;
		pIDeclarations->pVTbl->Clear(pIDeclarations);
		pIDeclarations->pVTbl->Release(pIDeclarations);

		/* Add undeclared enum types */
		pIDeclarations = pIScope->pVTbl->get_UndeclaredEnumTypes(pIScope);
		for (i = 0; i < pIDeclarations->pVTbl->Count(pIDeclarations); ++i) {
			pIUndeclaredEnumType = (IEcoToolchainAST1EnumType*)pIDeclarations->pVTbl->Item(pIDeclarations, i);
			description = pIStr ->pVTbl->Append(pIStr, description, pIUndeclaredEnumType->pVTbl->get_TypeName(pIUndeclaredEnumType));
			description = pIStr->pVTbl->Append(pIStr, description, " ");
		}
		pILog->pVTbl->InfoFormat(pILog, "%s|     Undeclared types: %s", offset, description);
		pIStr->pVTbl->Free(pIStr, description);
		description = 0;
		pIDeclarations->pVTbl->Clear(pIDeclarations);
		pIDeclarations->pVTbl->Release(pIDeclarations);

		/* Free */
		pIScope->pVTbl->Release(pIScope);
	}

    /* Try to get Global scope */
    result = pINode->pVTbl->QueryInterface(pINode, &IID_IEcoToolchainAST1GlobalScope, (void**)&pIGlobalScope);
    if (result == 0 && pIGlobalScope != 0) {
        /* Add function defenitions */
        pIDeclarations = pIGlobalScope->pVTbl->get_FunctionDefinitions(pIGlobalScope);
        for (i = 0; i < pIDeclarations->pVTbl->Count(pIDeclarations); ++i) {
            pIDefinition = (IEcoToolchainAST1FunctionDefinition*)pIDeclarations->pVTbl->Item(pIDeclarations, i);
            pIDeclaration = (IEcoToolchainAST1Declaration*)pIDefinition->pVTbl->get_Declaration(pIDefinition);
            description = pIStr->pVTbl->Append(pIStr, description, pIDeclaration->pVTbl->get_IdentifierName(pIDeclaration));
            description = pIStr->pVTbl->Append(pIStr, description, " ");
        }
        pILog->pVTbl->InfoFormat(pILog, "%s|     Definitions: %s", offset, description);
        pIStr->pVTbl->Free(pIStr, description);
        description = 0;
        pIDeclarations->pVTbl->Clear(pIDeclarations);
        pIDeclarations->pVTbl->Release(pIDeclarations);

        /* Free */
        pIGlobalScope->pVTbl->Release(pIGlobalScope);
    }

    pIChildren = pINode->pVTbl->get_Childrens(pINode);
    new_offset = pIStr->pVTbl->Clone(pIStr, offset);
    if (pINode->pVTbl->get_NextSibling(pINode) != 0 && pIChildren->pVTbl->Count(pIChildren) != 0)
        new_offset = pIStr->pVTbl->Append(pIStr, new_offset, "|  ");
    else if (pINode->pVTbl->get_NextSibling(pINode) == 0 && pIChildren->pVTbl->Count(pIChildren) != 0)
        new_offset = pIStr->pVTbl->Append(pIStr, new_offset, "   ");
    for (i = 0; i < pIChildren->pVTbl->Count(pIChildren); ++i) {
        pIChildNode = (IEcoTree1Node*)pIChildren->pVTbl->Item(pIChildren, i);
        OutputDiagnosticInfoOfASTNode(pILog, pIMem, pIStr, pIChildNode, new_offset);
    }
    pIStr->pVTbl->Free(pIStr, new_offset);
    return 1;
}

/*
 *
 * <сводка>
 *   Функция OutputDiagnosticInfoOfAST
 * </сводка>
 *
 * <описание>
 *   Функция OutputDiagnosticInfoOfAST - Вывод диагностической информации о дереве
 * </описание>
 *
 */
bool_t OutputDiagnosticInfoOfAST(/* in */ uint16_t langId, /* in */ IEcoLog1* pILog, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoString1* pIStr, /* in */ IEcoToolchainAST1* pIAST) {
    IEcoTree1* pITree = 0;
    IEcoTree1Node* pINode = 0;
    IEcoList1* pIForest = 0;
    uint32_t i = 0;
    int16_t result = 0;

    if (langId == ECO_LANG_ASM) {
        pILog->pVTbl->InfoFormat(pILog, "****************************** ASSEMBLER AST ******************************");
    }
    else if (langId == ECO_LANG_C89) {
        pILog->pVTbl->InfoFormat(pILog, "****************************** C89 AST ******************************");
    }
    else if (langId == ECO_LANG_OBJC) {
        pILog->pVTbl->InfoFormat(pILog, "****************************** OBJECTIVE C AST ******************************");
    }

    result = pIAST->pVTbl->QueryInterface(pIAST, &IID_IEcoTree1, (void**)&pITree);
    pIForest = pITree->pVTbl->get_Forest(pITree);
    for (i = 0; i < pIForest->pVTbl->Count(pIForest); ++i) {
        pILog->pVTbl->InfoFormat(pILog, "Tree[%i]", i);
        pINode = (IEcoTree1Node*)pIForest->pVTbl->Item(pIForest, i);
        OutputDiagnosticInfoOfASTNode(pILog, pIMem, pIStr, pINode, "");
    }
    pITree->pVTbl->Release(pITree);
    return 1;
}

