/* 
Análise de Desempenho

    Melhor Caso (O(1)):
    A chave está na primeira posição do vetor. Apenas 1 comparação é necessária.

    Pior Caso (O(n)):
    A chave não está no vetor ou está na última posição. Todas as n comparações são realizadas.

    Caso Médio (O(n)):
    Em média, a chave será encontrada na metade do vetor. Isso resulta em n/2 comparações, o que ainda é linear (O(n)).

Explicação:
A pesquisa linear sempre varre o vetor sequencialmente, 
independentemente da distribuição dos elementos. 
Mesmo com múltiplas ocorrências, a complexidade permanece linear, 
pois todos os elementos precisam ser verificados no pior caso.
*/