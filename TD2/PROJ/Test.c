#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para redirecionar stdin/stdout e executar o main
void run_main(const char *input_file, const char *output_file) {
    // Redireciona stdin para o arquivo de input
    freopen(input_file, "r", stdin);
    // Redireciona stdout para um arquivo temporário
    freopen(output_file, "w", stdout);
    
    // Chama a função main do programa
    extern int main(void);
    main();
    
    // Restaura stdin/stdout
    freopen("/dev/tty", "r", stdin);
    freopen("/dev/tty", "w", stdout);
}

// Função para comparar dois arquivos
int compare_files(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if (!f1 || !f2) return -1;

    char line1[1024], line2[1024];
    int result = 0;

    while (fgets(line1, sizeof(line1), f1) {
        if (!fgets(line2, sizeof(line2), f2)) {
            result = 1; // Arquivo 2 é menor
            break;
        }
        if (strcmp(line1, line2) != 0) {
            result = 1; // Conteúdo diferente
            break;
        }
    }

    if (!result && !feof(f2)) result = 1; // Arquivo 2 é maior

    fclose(f1);
    fclose(f2);
    return result;
}

// Caso de teste: verifica a saída do programa
void test_program_output(void) {
    const char *input_path = "input.txt";
    const char *expected_path = "expected.txt";
    const char *actual_path = "temp_output.txt";

    // Executa o programa com o input e salva a saída em temp_output.txt
    run_main(input_path, actual_path);

    // Compara a saída gerada com a esperada
    CU_ASSERT_EQUAL(compare_files(actual_path, expected_path), 0);

    // Remove o arquivo temporário (opcional)
    remove(actual_path);
}

// Configuração do CUnit
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Teste Programa", NULL, NULL);
    CU_add_test(suite, "Teste Saída do Programa", test_program_output);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}