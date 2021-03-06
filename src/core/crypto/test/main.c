#include <stdio.h> /* fprintf */

#include "../aes_encryption.h"
#include "../../beans/file_desc.h"
#include "../rsa_encryption.h"

int main(void)
{
    FileDesc_t *f_desc = aes_encrypt_file("text.txt");

    if(f_desc != NULL)
    {
        fprintf(stdout, "[TEST] File encrypted:\n");
        fprintf(stdout, "[TEST] FILE_ID: %s\n", f_desc->file_id);
        fprintf(stdout, "[TEST] SIZE:    %s\n", f_desc->size);
        fprintf(stdout, "[TEST] PATH:    %s\n", f_desc->path);
        fprintf(stdout, "[TEST] SYM_KEY: %s\n", f_desc->symmetric_key);
        fprintf(stdout, "[TEST] IV:      %s\n", f_desc->initialisation_vector);
    }
    else
    {
        fprintf(stderr, "[TEST] Encrypt failed.\n");
    }

    const char *file_dec_path;
    if((file_dec_path = aes_decrypt_file(f_desc)) != NULL)
    {
        fprintf(stdout, "[TEST] File decrypted here: %s\n", file_dec_path);
    }
    else
    {
        fprintf(stderr, "[TEST] Decrypt failed.\n");
    }

    char *msg = "Bonjour, j'aimerais être chiffré en RSA.";
    fprintf(stdout, "\n[TEST] Message: %s\n", msg);

    const char *enc_msg =
        rsa_encrypt_msg("/home/julien/.config/sipd/keys/julien-sipd-rsa.pub", msg);
    fprintf(stdout, "[TEST] Encrypted message: %s\n", enc_msg);

    const char *dec_msg =
        rsa_decrypt_msg("/home/julien/.config/sipd/keys/julien-sipd-rsa", enc_msg);
    fprintf(stdout, "[TEST] Decrypted message: %s\n", dec_msg);

    fprintf(stdout, "[TEST] Asserting acknowledge....");
    const char *enc_ack =
        rsa_encrypt_msg("/home/julien/.config/sipd/keys/julien-sipd-rsa.pub", MSG_ACK);

    rsa_assert_ack("/home/julien/.config/sipd/keys/julien-sipd-rsa", enc_ack);
    fprintf(stdout, " Ok.\n");

    return 0;
}
