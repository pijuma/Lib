## Proteger todas pontes com a menor quantidade de arestas possiveis? 
Conectar folhas pela ordem do euler tour conectando sempre (i, i+mid) = forma ótima 
## Proteger todos vértices de articulação min arestas
 pegar block cut tree (folhas = L) max(L/2, V-1) sendo V o maior grau de um ponto de articulacao
 Cada folha precisa de uma aresta e preciso proteger o de maior grau, se separar ele preciso de V-1 
 arestas pra juntar... por isso o valor. 
