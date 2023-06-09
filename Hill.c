#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int pgcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return pgcd(b, a % b);
}

int inverserLaMatrice(int key[][3])
{
    int det = 0;
    det += key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1]);
    det -= key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0]);
    det += key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]);

    if (pgcd(det, 26) != 1)
    {
        printf("La  matrice(cle) est inversible n'est pas iversi\n");
        return 0;
    }

    return 1;
}

void encrypt(char *message, int key[][3])
{
    int i, j, k, len, row, col;
    int plain[3], cipher[3];

    len = strlen(message);
    if (len % 3 != 0)
    {
        printf("La taille du message doit etre un multiple de 3!\n");
        return;
    }

    for (i = 0; i < len; i += 3)
    {
        for (j = 0; j < 3; j++)
        {
            plain[j] = message[i + j] - 'a';
        }

        for (j = 0; j < 3; j++)
        {
            cipher[j] = 0;
            for (k = 0; k < 3; k++)
            {
                cipher[j] += key[j][k] * plain[k];
            }
            cipher[j] = mod(cipher[j], 26);
        }

        for (j = 0; j < 3; j++)
        {
            message[i + j] = cipher[j] + 'a';
        }
    }

    printf("Encrypted message: %s\n", message);
}

void decrypt(char *message, int key[][3])
{
    int i, j, k, len, row, col, det, inv_det, adj[3][3];
    int cipher[3], plain[3];

    len = strlen(message);
    if (len % 3 != 0)
    {
        printf("La taille du message doit etre un multiple de 3!\n");
        return;
    }

    det = 0;
    det += key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1]);
    det -= key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0]);
    det += key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]);

    inv_det = 0;
    for (i = 1; i <= 26; i++)
    {
        if ((i * det) % 26 == 1)
        {
            inv_det = i;
            break;
        }
    }

    if (!inverserLaMatrice(key))
    {
        return;
    }

    adj[0][0] = (key[1][1] * key[2][2] - key[1][2] * key[2][1]);
    adj[0][1] = -(key[0][1] * key[2][2] - key[0][2] * key[2][1]);
    adj[0][2] = (key[0][1] * key[1][2] - key[0][2] * key[1][1]);
    adj[1][0] = -(key[1][0] * key[2][2] - key[1][2] * key[2][0]);
    adj[1][1] = (key[0][0] * key[2][2] - key[0][2] * key[2][0]);
    adj[1][2] = -(key[0][0] * key[1][2] - key[0][2] * key[1][0]);
    adj[2][0] = (key[1][0] * key[2][1] - key[1][1] * key[2][0]);
    adj[2][1] = -(key[0][0] * key[2][1] - key[0][1] * key[2][0]);
    adj[2][2] = (key[0][0] * key[1][1] - key[0][1] * key[1][0]);

    for (i = 0; i < len; i += 3)
    {
        for (j = 0; j < 3; j++)
        {
            cipher[j] = message[i + j] - 'a';
        }

        for (j = 0; j < 3; j++)
        {
            plain[j] = 0;
            for (k = 0; k < 3; k++)
            {
                plain[j] += adj[j][k] * cipher[k];
            }
            plain[j] = mod(inv_det * plain[j], 26);
        }

        for (j = 0; j < 3; j++)
        {
            message[i + j] = plain[j] + 'a';
        }
    }

    printf("le message decrypter est : %s\n", message);
}

int main()
{
    char message[100];
    int key[3][3] = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}};

    printf("Entrez le message a Crypter: ");
    scanf("%s", message);
    printf("Chiffrement en Cours ...\n");
    encrypt(message, key);
    printf("Dechiffrement message...\n");
    decrypt(message, key);

    return 0;
}