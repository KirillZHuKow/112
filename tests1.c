void Test1()
{
    int i;
    //Creating 1st test string
    struct StringN* sTest1 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest1 = 7;
    int elSize = sizeof(char);
    char symbols1[] = {"Pointer"};
    sTest1->dimension = sizeTest1;
    sTest1->elSize = elSize;
    sTest1->symbols = (void*)symbols1;
    //Test CreateFromValues
    char symBuf[] = {"Pointer"};
    struct StringN* sBuf = (struct StringN*)malloc(sizeof(struct StringN));
    sBuf->dimension = sizeTest1;
    sBuf->elSize = elSize;
    sBuf = CreateFromValuesChar(sizeTest1, elSize, (void*)symBuf);
    for (i = 0; i < 7; i++)
    {
        assert((*(char*)GetNChar(i, sBuf))==*(symBuf + i * sizeof(char)));
    }
    //Test Conc
    int sizeTest2 = 4;
    char symbols2[] = "Name";
    struct StringN* sTest2 = (struct StringN*)malloc(sizeof(struct StringN));
    sTest2->dimension = sizeTest2;
    sTest2->elSize = elSize;
    sTest2->symbols = symbols2;
    struct StringN* sTestT = (struct StringN*)malloc(sizeof(char));
    sTestT->dimension = sizeTest2;
    sTestT->elSize = elSize;
    sTestT = CreateFromValuesChar(sizeTest2, elSize, symbols2);
    struct StringN* strConc = (struct StringN*)malloc(sizeof(struct StringN));
    strConc->dimension = sizeTest1 + sizeTest2;
    strConc->elSize = elSize;
    strConc = ConcChar(sTest1, sTestT);
    char symbolsConc[12] = {"PointerName"};
    for (i = 0; i < 11; i++)
    {
        assert((*(char*)GetNChar(i, strConc))==*(symbolsConc + i * sizeof(char)));
    }
    free(sTestT);
    free(strConc);
    //Test GetN
    assert((*(char*)GetNChar(0, sTest1))=='P');
    //Test SetN
    char newValue = 'd';
    char* pnewValue = &newValue;
    char symbolsBuf[9] = {"dointer"};
    SetNChar(0, pnewValue, sTest1);
    assert((*(char*)sTest1->symbols)==*symbolsBuf);
    //Test Subs
    struct StringN* sTest3 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest3 = 9;
    char symbols3[9] = {"Pointer"};
    sTest3->dimension = sizeTest3;
    sTest3->elSize = elSize;
    sTest3->symbols = (void*)symbols3;
    struct StringN* strSubs = (struct StringN*)malloc(sizeof(struct StringN));
    strSubs->dimension = sizeTest1;
    strSubs->elSize = elSize;
    strSubs = SubsChar(sTest3, 1, 4);
    char symbolsSubs[6] = {"oint"};
    for (i = 0; i < 4; i++)
    {
        assert((*(char*)GetNChar(i, strSubs))==*(symbolsSubs + i * sizeof(char)));
    }
    free(strSubs);
    //Test Recod
    struct StringN* sTest4 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest4 = 7;
    char symbols4[] = {"Pointer"};
    sTest4->dimension = sizeTest4;
    sTest4->elSize = elSize;
    sTest4->symbols = (void*)symbols4;
    struct StringN* strBijection = (struct StringN*)malloc(sizeof(struct StringN));
    strBijection->dimension = sizeTest1;
    strBijection->elSize = elSize;
    strBijection = RecodChar(sTest4, BijectionChar);
    char symbolsRecod[] = "retnioP";
    for (i = 0; i < 7; i++)
    {
        assert((*(char*)GetNChar(i, strBijection))==*(symbolsRecod + i * sizeof(char)));
    }
    free(strBijection);
    free(sTest4);
    printf("Assertion1 succeed\n");
}

void Test2()
{
    int i;
    //Creating 1st test string
    struct StringN* sTest1 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest1 = 4;
    int elSize = sizeof(char);
    char symbols1[] = {"Void"};
    sTest1->dimension = sizeTest1;
    sTest1->elSize = elSize;
    sTest1->symbols = (void*)symbols1;
    //Test CreateFromValues
    char symBuf[] = {"Void"};
    struct StringN* sBuf = (struct StringN*)malloc(sizeof(struct StringN));
    sBuf->dimension = sizeTest1;
    sBuf->elSize = elSize;
    sBuf = CreateFromValuesChar(sizeTest1, elSize, (void*)symBuf);
    for (i = 0; i < 4; i++)
    {
        assert((*(char*)GetNChar(i, sBuf))==*(symBuf + i * sizeof(char)));
    }
    //Test Conc
    int sizeTest2 = 8;
    char symbols2[] = {"Function"};
    struct StringN* sTest2 = (struct StringN*)malloc(sizeof(struct StringN));
    sTest2->dimension = sizeTest2;
    sTest2->elSize = elSize;
    sTest2->symbols = symbols2;
    struct StringN* sTestT = (struct StringN*)malloc(sizeof(char));
    sTestT->dimension = sizeTest2;
    sTestT->elSize = elSize;
    sTestT = CreateFromValuesChar(sizeTest2, elSize, symbols2);
    struct StringN* strConc = (struct StringN*)malloc(sizeof(struct StringN));
    strConc->dimension = sizeTest1 + sizeTest2;
    strConc->elSize = elSize;
    strConc = ConcChar(sTest1, sTestT);
    char symbolsConc[] = {"VoidFunction"};
    for (i = 0; i < 12; i++)
    {
        assert((*(char*)GetNChar(i, strConc))==*(symbolsConc + i * sizeof(char)));
    }
    free(sTestT);
    free(strConc);
    //Test GetN
    assert((*(char*)GetNChar(0, sTest1))=='V');
    //Test SetN
    char newValue = 'd';
    char* pnewValue = &newValue;
    char symbolsBuf[] = {"doid"};
    SetNChar(0, pnewValue, sTest1);
    assert((*(char*)sTest1->symbols)==*symbolsBuf);
    //Test Subs
    struct StringN* sTest3 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest3 = 5;
    char symbols3[] = {"Void"};
    sTest3->dimension = sizeTest3;
    sTest3->elSize = elSize;
    sTest3->symbols = (void*)symbols3;
    struct StringN* strSubs = (struct StringN*)malloc(sizeof(struct StringN));
    strSubs->dimension = sizeTest1;
    strSubs->elSize = elSize;
    strSubs = SubsChar(sTest3, 0, 2);
    char symbolsSubs[] = {"Voi"};
    for (i = 0; i < 3; i++)
    {
        assert((*(char*)GetNChar(i, strSubs))==*(symbolsSubs + i * sizeof(char)));
    }
    free(strSubs);
    //Test Recod
    struct StringN* sTest4 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest4 = 4;
    char symbols4[] = {"Void"};
    sTest4->dimension = sizeTest4;
    sTest4->elSize = elSize;
    sTest4->symbols = (void*)symbols4;
    struct StringN* strBijection = (struct StringN*)malloc(sizeof(struct StringN));
    strBijection->dimension = sizeTest1;
    strBijection->elSize = elSize;
    strBijection = RecodChar(sTest4, BijectionChar);
    char symbolsRecod[] = "dioV";
    for (i = 0; i < 4; i++)
    {
        assert((*(char*)GetNChar(i, strBijection))==*(symbolsRecod + i * sizeof(char)));
    }
    free(strBijection);
    free(sTest4);
    printf("Assertion2 succeed\n");
}

void Test3()
{
    int i;
    //Creating 1st test string
    struct StringN* sTest1 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest1 = 4;
    int elSize = sizeof(char);
    char symbols1[] = {"Book"};
    sTest1->dimension = sizeTest1;
    sTest1->elSize = elSize;
    sTest1->symbols = (void*)symbols1;
    //Test CreateFromValues
    char symBuf[] = {"Book"};
    struct StringN* sBuf = (struct StringN*)malloc(sizeof(struct StringN));
    sBuf->dimension = sizeTest1;
    sBuf->elSize = elSize;
    sBuf = CreateFromValuesChar(sizeTest1, elSize, (void*)symBuf);
    for (i = 0; i < 4; i++)
    {
        assert((*(char*)GetNChar(i, sBuf))==*(symBuf + i * sizeof(char)));
    }
    //Test Conc
    int sizeTest2 = 8;
    char symbols2[] = {"Integral"};
    struct StringN* sTest2 = (struct StringN*)malloc(sizeof(struct StringN));
    sTest2->dimension = sizeTest2;
    sTest2->elSize = elSize;
    sTest2->symbols = symbols2;
    struct StringN* sTestT = (struct StringN*)malloc(sizeof(char));
    sTestT->dimension = sizeTest2;
    sTestT->elSize = elSize;
    sTestT = CreateFromValuesChar(sizeTest2, elSize, symbols2);
    struct StringN* strConc = (struct StringN*)malloc(sizeof(struct StringN));
    strConc->dimension = sizeTest1 + sizeTest2;
    strConc->elSize = elSize;
    strConc = ConcChar(sTest1, sTestT);
    char symbolsConc[] = {"BookIntegral"};
    for (i = 0; i < 12; i++)
    {
        assert((*(char*)GetNChar(i, strConc))==*(symbolsConc + i * sizeof(char)));
    }
    free(sTestT);
    free(strConc);
    //Test GetN
    assert((*(char*)GetNChar(1, sTest1))=='o');
    //Test SetN
    char newValue = 'r';
    char* pnewValue = &newValue;
    char symbolsBuf[] = {"rook"};
    SetNChar(0, pnewValue, sTest1);
    assert((*(char*)sTest1->symbols)==*symbolsBuf);
    //Test Subs
    struct StringN* sTest3 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest3 = 5;
    char symbols3[] = {"Book"};
    sTest3->dimension = sizeTest3;
    sTest3->elSize = elSize;
    sTest3->symbols = (void*)symbols3;
    struct StringN* strSubs = (struct StringN*)malloc(sizeof(struct StringN));
    strSubs->dimension = sizeTest1;
    strSubs->elSize = elSize;
    strSubs = SubsChar(sTest3, 1, 2);
    char symbolsSubs[] = {"oo"};
    for (i = 0; i < 2; i++)
    {
        assert((*(char*)GetNChar(i, strSubs))==*(symbolsSubs + i * sizeof(char)));
    }
    free(strSubs);
    //Test Recod
    struct StringN* sTest4 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest4 = 4;
    char symbols4[] = {"Book"};
    sTest4->dimension = sizeTest4;
    sTest4->elSize = elSize;
    sTest4->symbols = (void*)symbols4;
    struct StringN* strBijection = (struct StringN*)malloc(sizeof(struct StringN));
    strBijection->dimension = sizeTest1;
    strBijection->elSize = elSize;
    strBijection = RecodChar(sTest4, BijectionChar);
    char symbolsRecod[] = "kooB";
    for (i = 0; i < 4; i++)
    {
        assert((*(char*)GetNChar(i, strBijection))==*(symbolsRecod + i * sizeof(char)));
    }
    free(strBijection);
    free(sTest4);
    printf("Assertion3 succeed\n");
}
