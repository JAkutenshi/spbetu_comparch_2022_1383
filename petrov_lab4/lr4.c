#include <stdio.h>
int main(){
    system("chcp 1251 > nul");
    printf ("������ ���������\n������ 1383\n������� 16\n�������������� ��������� �� ������� ������ ������� ���� � ��������� � ������������ � ��������� ��������������, ��������� ������� ������� ������ ���������� � �������� ������ ���������������.\n");
    char input[81];
    char output[81];
    fgets(input,81,stdin);
    asm(

        "letter_check: \n"
            "lodsb \n"
            "cmp al, 0\n"
            "je finish \n"

            "cmp al, 192\n"//�����
            "je A_sym \n"
            "cmp al, 224\n"//������
            "je a_sym \n"

            "cmp al, 193\n"//�����
            "je B_sym \n"
            "cmp al, 225\n"//�����
            "je b_sym \n"

            "cmp al, 194\n"//�����
            "je V_sym \n"
            "cmp al, 226\n"//�����
            "je v_sym \n"

            "cmp al, 195\n"//�����
            "je G_sym \n"
            "cmp al, 227\n"//�����
            "je g_sym \n"

            "cmp al, 196\n"//�����
            "je D_sym \n"
            "cmp al, 228\n"//�����
            "je d_sym \n"

            "cmp al, 197\n"//�����
            "je E_sym \n"
            "cmp al, 229\n"//�����
            "je e_sym \n"

            "cmp al, 198\n"//�����
            "je J_sym \n"
            "cmp al, 230\n"//�����
            "je j_sym \n"

            "cmp al, 199\n"//�����
            "je Z_sym \n"
            "cmp al, 231\n"//�����
            "je z_sym \n"

            "cmp al, 200\n"//�����
            "je I_sym \n"
            "cmp al, 232\n"//�����
            "je i_sym \n"

            "cmp al, 201\n"//�����
            "je I_sym \n"
            "cmp al, 233\n"//�����
            "je i_sym \n"

            "cmp al, 202\n"//�����
            "je K_sym \n"
            "cmp al, 234\n"//�����
            "je k_sym \n"

            "cmp al, 203\n"//�����
            "je L_sym \n"
            "cmp al, 235\n"//�����
            "je l_sym \n"

            "cmp al, 204\n"//�����
            "je M_sym \n"
            "cmp al, 236\n"//�����
            "je m_sym \n"

            "cmp al, 205\n"//�����
            "je N_sym \n"
            "cmp al, 237\n"//�����
            "je n_sym \n"

            "cmp al, 206\n"//�����
            "je O_sym \n"
            "cmp al, 238\n"//�����
            "je o_sym \n"

            "cmp al, 207\n"//�����
            "je P_sym \n"
            "cmp al, 239\n"//�����
            "je p_sym \n"

            "cmp al, 208\n"//�����
            "je R_sym \n"
            "cmp al, 240\n"//�����
            "je r_sym \n"

            "cmp al, 209\n"//�����
            "je S_sym \n"
            "cmp al, 241\n"//�����
            "je s_sym \n"

            "cmp al, 210\n"//�����
            "je T_sym \n"
            "cmp al, 242\n"//�����
            "je t_sym \n"

            "cmp al, 211\n"//�����
            "je U_sym \n"
            "cmp al, 243\n"//�����
            "je u_sym \n"

            "cmp al, 212\n"//�����
            "je F_sym \n"
            "cmp al, 244\n"//�����
            "je f_sym \n"

            "cmp al, 213\n"//�����
            "je Kh_sym \n"
            "cmp al, 245\n"//�����
            "je kh_sym \n"

            "cmp al, 214\n"//�����
            "je C_sym \n"
            "cmp al, 246\n"//�����
            "je c_sym \n"

            "cmp al, 215\n"//�����
            "je Ch_sym \n"
            "cmp al, 247\n"//�����
            "je ch_sym \n"

            "cmp al, 216\n"//�����
            "je Sh_sym \n"
            "cmp al, 248\n"//�����
            "je sh_sym \n"

            "cmp al, 217\n"//�����
            "je S�_sym \n"
            "cmp al, 249\n"//�����
            "je s�_sym \n"

            "cmp al, 218\n"//�����
            "je letter_check \n"
            "cmp al, 250\n"//�����
            "je letter_check \n"

            "cmp al, 219\n"//�����
            "je Y_sym \n"
            "cmp al, 251\n"//�����
            "je y_sym \n"

            "cmp al, 220\n"//�����
            "je letter_check \n"
            "cmp al, 252\n"//�����
            "je letter_check \n"

            "cmp al, 221\n"//�����
            "je E_sym \n"
            "cmp al, 253\n"//�����
            "je e_sym \n"

            "cmp al, 222\n"//�����
            "je Iu_sym \n"
            "cmp al, 254\n"//�����
            "je iu_sym \n"

            "cmp al, 223\n"//�����
            "je Ia_sym \n"
            "cmp al, 255\n"//�����
            "je ia_sym \n"

            "stosb \n"
            "jmp letter_check \n"

        "A_sym: \n"//�
            "mov al, 65 \n"
            "stosb \n"
            "jmp letter_check \n"

        "a_sym: \n"//a
            "mov al, 97 \n"
            "stosb \n"
            "jmp letter_check \n"

        "B_sym: \n"//B
            "mov al, 66 \n"
            "stosb \n"
            "jmp letter_check \n"

        "b_sym: \n"//b
            "mov al, 98 \n"
            "stosb \n"
            "jmp letter_check \n"

        "C_sym: \n"//C
            "mov al, 67 \n"
            "stosb \n"
            "jmp letter_check \n"

        "c_sym: \n"//c
            "mov al, 99 \n"
            "stosb \n"
            "jmp letter_check \n"

        "D_sym: \n"//D
            "mov al, 68 \n"
            "stosb \n"
            "jmp letter_check \n"

        "d_sym: \n"//d
            "mov al, 100 \n"
            "stosb \n"
            "jmp letter_check \n"

        "E_sym: \n"//E
            "mov al, 69 \n"
            "stosb \n"
            "jmp letter_check \n"

        "e_sym: \n"//e
            "mov al, 101 \n"
            "stosb \n"
            "jmp letter_check \n"

        "F_sym: \n"//F
            "mov al, 70 \n"
            "stosb \n"
            "jmp letter_check \n"

        "f_sym: \n"//f
            "mov al, 102 \n"
            "stosb \n"
            "jmp letter_check \n"

        "G_sym: \n"//G
            "mov al, 71 \n"
            "stosb \n"
            "jmp letter_check \n"

        "g_sym: \n"//g
            "mov al, 103 \n"
            "stosb \n"
            "jmp letter_check \n"

        "H_sym: \n"//H
            "mov al, 72 \n"
            "stosb \n"
            "jmp letter_check \n"

        "h_sym: \n"//h
            "mov al, 104 \n"
            "stosb \n"
            "jmp letter_check \n"

        "I_sym: \n"//I
            "mov al, 73 \n"
            "stosb \n"
            "jmp letter_check \n"

        "i_sym: \n"//i
            "mov al, 105 \n"
            "stosb \n"
            "jmp letter_check \n"

        "J_sym: \n"//J
            "mov al, 74 \n"
            "stosb \n"
            "jmp letter_check \n"

        "j_sym: \n"//j
            "mov al, 106 \n"
            "stosb \n"
            "jmp letter_check \n"

        "K_sym: \n"//K
            "mov al, 75 \n"
            "stosb \n"
            "jmp letter_check \n"

        "k_sym: \n"//k
            "mov al, 107 \n"
            "stosb \n"
            "jmp letter_check \n"

        "L_sym: \n"//L
            "mov al, 76 \n"
            "stosb \n"
            "jmp letter_check \n"

        "l_sym: \n"//l
            "mov al, 108 \n"
            "stosb \n"
            "jmp letter_check \n"

        "M_sym: \n"//M
            "mov al, 77 \n"
            "stosb \n"
            "jmp letter_check \n"

        "m_sym: \n"//m
            "mov al, 109 \n"
            "stosb \n"
            "jmp letter_check \n"

        "N_sym: \n"//N
            "mov al, 78 \n"
            "stosb \n"
            "jmp letter_check \n"

        "n_sym: \n"//n
            "mov al, 110 \n"
            "stosb \n"
            "jmp letter_check \n"

        "O_sym: \n"//O
            "mov al, 79 \n"
            "stosb \n"
            "jmp letter_check \n"

        "o_sym: \n"//o
            "mov al, 111 \n"
            "stosb \n"
            "jmp letter_check \n"

        "P_sym: \n"//P
            "mov al, 80 \n"
            "stosb \n"
            "jmp letter_check \n"

        "p_sym: \n"//p
            "mov al, 112 \n"
            "stosb \n"
            "jmp letter_check \n"

        "R_sym: \n"//R
            "mov al, 82 \n"
            "stosb \n"
            "jmp letter_check \n"

        "r_sym: \n"//r
            "mov al, 114 \n"
            "stosb \n"
            "jmp letter_check \n"   

        "S_sym: \n"//S
            "mov al, 83 \n"
            "stosb \n"
            "jmp letter_check \n"

        "s_sym: \n"//s
            "mov al, 115 \n"
            "stosb \n"
            "jmp letter_check \n"

        "T_sym: \n"//T
            "mov al, 84 \n"
            "stosb \n"
            "jmp letter_check \n"

        "t_sym: \n"//t
            "mov al, 116 \n"
            "stosb \n"
            "jmp letter_check \n"

        "U_sym: \n"//U
            "mov al, 85 \n"
            "stosb \n"
            "jmp letter_check \n"

        "u_sym: \n"//u
            "mov al, 117 \n"
            "stosb \n"
            "jmp letter_check \n"

        "V_sym: \n"//V
            "mov al, 86 \n"
            "stosb \n"
            "jmp letter_check \n"

        "v_sym: \n"//v
            "mov al, 118 \n"
            "stosb \n"
            "jmp letter_check \n"

        "Y_sym: \n"//Y
            "mov al, 89 \n"
            "stosb \n"
            "jmp letter_check \n"

        "y_sym: \n"//y
            "mov al, 121 \n"
            "stosb \n"
            "jmp letter_check \n"

        "Z_sym: \n"//Z
            "mov al, 90 \n"
            "stosb \n"
            "jmp letter_check \n"

        "z_sym: \n"//z
            "mov al, 122 \n"
            "stosb \n"
            "jmp letter_check \n"
         
        "Kh_sym: \n"//Kh
            "mov al, 75 \n"
            "stosb \n"
            "mov al, 104 \n"
            "stosb \n"
            "jmp letter_check \n"

        "kh_sym: \n"//kh
            "mov al, 107 \n"
            "stosb \n"
            "mov al, 104 \n"
            "stosb \n"
            "jmp letter_check \n"

        "Ch_sym: \n"//Ch
            "mov al, 67 \n"
            "stosb \n"
            "mov al, 104 \n"
            "stosb \n"
            "jmp letter_check \n"

        "ch_sym: \n"//ch
            "mov al, 99 \n"
            "stosb \n"
            "mov al, 104 \n"
            "stosb \n"
            "jmp letter_check \n"

        "Sh_sym: \n"//Sh
            "mov al, 83 \n"
            "stosb \n"
            "mov al, 104 \n"
            "stosb \n"
            "jmp letter_check \n"

        "sh_sym: \n"//sh
            "mov al, 115 \n"
            "stosb \n"
            "mov al, 104 \n"
            "stosb \n"
            "jmp letter_check \n"

        "S�_sym: \n"//S�
            "mov al, 83 \n"
            "stosb \n"
            "mov al, 99 \n"
            "stosb \n"
            "jmp letter_check \n"

        "s�_sym: \n"//s�
            "mov al, 115 \n"
            "stosb \n"
            "mov al, 99 \n"
            "stosb \n"
            "jmp letter_check \n"

        "Iu_sym: \n"//Iu
            "mov al, 73 \n"
            "stosb \n"
            "mov al, 117 \n"
            "stosb \n"
            "jmp letter_check \n"

        "iu_sym: \n"//iu
            "mov al, 105 \n"
            "stosb \n"
            "mov al, 117 \n"
            "stosb \n"
            "jmp letter_check \n"

        "Ia_sym: \n"//Ia
            "mov al, 73 \n"
            "stosb \n"
            "mov al, 97 \n"
            "stosb \n"
            "jmp letter_check \n"

        "ia_sym: \n"//ia
            "mov al, 105 \n"
            "stosb \n"
            "mov al, 97 \n"
            "stosb \n"
            "jmp letter_check \n"

        "finish: \n"
            "stosb \n"

        :
        : "D"(output), "S"(input)
        : 
    );



    printf("%s\n", &output);
    FILE * file = fopen ("out.txt", "w");
    fprintf(file, "%s", output);
    fclose (file);
};