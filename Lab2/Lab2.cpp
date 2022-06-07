#include <iostream>

using namespace std;

int* Select(int* M, int n)
{
    int min = 0, t = 0;
    _asm
    {
        mov eax, M
        mov ecx, 0
        mov esi, -1

        cycle:
        inc esi
            mov ebx, n
            dec ebx
            cmp esi, ebx
            jae out1
            jmp oper1

            oper1 :
        mov ecx, esi

            mov ebx, esi
            inc ebx
            mov edi, ebx

            cycle_2 :
        cmp edi, n
            jae go1
            jmp cmp1

            cmp1 :
        mov ebx, [eax + 4 * edi]
            mov edx, [eax + 4 * ecx]
            inc edi

            cmp ebx, edx
            jb move1
            jmp cycle_2

            move1 :
        dec edi
            mov ecx, edi
            inc edi
            jmp cycle_2


            go1 :
        mov ebx, [eax + 4 * esi]
            mov edx, [eax + 4 * ecx]

            mov   t, edx
            mov   edx, ebx
            mov   ebx, t
            mov[eax + 4 * esi], ebx
            mov[eax + 4 * ecx], edx

            jmp cycle

            out1 :
    }

    return M;
}

int* Bubble(int* M, int n)
{
    int i = 0, j = 0, t = 0;

    _asm
    {
        mov eax, M
        mov ebx, 0
        mov ecx, 0

        cycle:

    cycle_2:

        mov ebx, [eax + 4 * ecx]
            add ecx, 1
            mov edx, [eax + 4 * ecx]
            sub ecx, 1
            cmp ebx, edx
            ja swap1
            jmp go1
            swap1 :
        mov   t, edx
            mov   edx, ebx
            mov   ebx, t
            mov[eax + 4 * ecx], ebx
            add ecx, 1
            mov[eax + 4 * ecx], edx
            sub ecx, 1

            go1:
        inc ecx
            mov ebx, n
            sub ebx, 1
            sub ebx, j
            cmp ecx, ebx
            je out2
            jmp cycle_2

            out2 :


        mov ecx, j
            add ecx, 1
            mov j, ecx

            mov ebx, n
            sub ebx, 1
            cmp ecx, ebx
            je out1
            mov ecx, 0
            jmp cycle

            out1 :
    }

    return M;
}


int main()
{
    setlocale(LC_ALL, "Russian");

    int size = 5;
    int k = 1;

    int* mas;
    mas = new int[size];
    for (int i = 0; i < size; i++)  mas[i] = rand() % 100;
       
    for (int i = 0; i < size; i++) cout << mas[i] << " ";   
    cout << endl;

    cout << "Введите 1 - сортировка пузырьком / 2 - сортировка выбором" << endl;
    cin >> k;
    switch (k)
    {
    case 1:
        mas = Bubble(mas, size);
        break;
    case 2:
        mas = Select(mas, size);
        break;
    }

    for (int i = 0; i < size; i++) cout << mas[i] << " ";
}