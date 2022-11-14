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
 *   Данный файл описывает прототипы функций описания грамматики для C89
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoFSM1.h"
#include "IEcoToolchainBNF1.h"

IEcoFSM1StateMachine* GetFAForLAOfC89 (IEcoFSM1* pIFSM);
IEcoToolchainBNF1* GetBNFForSAOfC89(IEcoToolchainBNF1* pIBNF);
