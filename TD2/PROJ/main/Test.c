#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run_TDfinal(const char *exe, const char *input_file, const char *output_file) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "%s < %s > %s", exe, input_file, output_file);
    return system(cmd);
}

int compare_files(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if (!f1 || !f2) return -1;
    
    int res = 0;
    char line1[1024], line2[1024];
    
    while (fgets(line1, sizeof(line1), f1)) {
        // Remove espaços e quebras de linha
        line1[strcspn(line1, "\n")] = '\0';
        if (!fgets(line2, sizeof(line2), f2)) {
            res = 1;
            break;
        }
        line2[strcspn(line2, "\n")] = '\0';
        
        if (strcmp(line1, line2) != 0) {
            res = 1;
            break;
        }
    }
    
    // Verifica se ambos chegaram ao fim
    if (!res && (fgets(line2, sizeof(line2), f2))) {
        res = 1;
    }  
        
    fclose(f1);
    fclose(f2);
    return res;
}

void test_empty_lines(void) { 
    CU_ASSERT_EQUAL(run_TDfinal("./TDfinal.exe", "../input/input_empty.txt", "tmp.txt"), 0);
    CU_ASSERT_EQUAL(compare_files("tmp.txt", "../test/exp_empty.txt"), 0); 
    remove("tmp.txt"); 
}

void test_zero_N(void) { 
    CU_ASSERT_EQUAL(run_TDfinal("./TDfinal.exe", "../input/input_zero.txt", "tmp1.txt"), 0);
    CU_ASSERT_EQUAL(compare_files("tmp1.txt", "../test/exp_zero.txt"), 0); 
    remove("tmp1.txt"); 
}

void test_punctuation_only(void) { 
    CU_ASSERT_EQUAL(run_TDfinal("./TDfinal.exe", "../input/input_punc.txt", "tmp2.txt"), 0);
    CU_ASSERT_EQUAL(compare_files("tmp2.txt", "../test/exp_punc.txt"), 0); 
    remove("tmp2.txt"); 
}

void test_case_sensitivity(void) { 
    CU_ASSERT_EQUAL(run_TDfinal("./TDfinal.exe", "../input/input_case.txt", "tmp3.txt"), 0);
    CU_ASSERT_EQUAL(compare_files("tmp3.txt", "../test/exp_case.txt"), 0); 
    remove("tmp3.txt"); 
}

void test_N_larger_than_vocab(void) { 
    CU_ASSERT_EQUAL(run_TDfinal("./TDfinal.exe", "../input/input_small.txt", "tmp4.txt"), 0);
    CU_ASSERT_EQUAL(compare_files("tmp4.txt", "../test/exp_small.txt"), 0); 
    remove("tmp4.txt"); 
}

void test_program_output(void) { 
    CU_ASSERT_EQUAL(run_TDfinal("./TDfinal.exe", "../input/input.txt", "temp_output.txt"), 0);
    CU_ASSERT_EQUAL(compare_files("temp_output.txt", "../test/expected.txt"), 0); 
    remove("temp_output.txt"); 
}

void test_program_output_2(void) { 
    CU_ASSERT_EQUAL(run_TDfinal("./TDfinal.exe", "../input/input2.txt", "temp_output_2.txt"), 0);
    CU_ASSERT_EQUAL(compare_files("temp_output_2.txt", "../test/expected2.txt"), 0); 
    remove("temp_output_2.txt"); 
}

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS) return CU_get_error();
    CU_pSuite suite = CU_add_suite("Teste Programa", NULL, NULL);
    CU_add_test(suite, "Linhas vazias", test_empty_lines);
    CU_add_test(suite, "N = 0", test_zero_N);
    CU_add_test(suite, "Só pontuação", test_punctuation_only);
    CU_add_test(suite, "Case sensitivity", test_case_sensitivity);
    CU_add_test(suite, "N > vocabulário", test_N_larger_than_vocab);
    CU_add_test(suite, "Teste Genérico", test_program_output);
    CU_add_test(suite, "Teste Genérico 2", test_program_output_2);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests(); 
    CU_cleanup_registry();
    return CU_get_error();
}