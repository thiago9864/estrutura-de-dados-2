# -*- coding: utf-8 -*-
"""
Created on Sat Oct 12 12:33:21 2019

@author: Thiago
"""
import pandas as pd
import os
import matplotlib.pyplot as plt

path_raiz = os.getcwd()

file_tree = []
for root, directories, files in os.walk(path_raiz):
    for file in files:
        if ('.csv' in file):
            file_tree.append(os.path.join(root, file))
            

#csv_medio = []
dataframes = []
colunas = [u'Número de Testes','Algoritmo',u'Tempo de Execução',u'Taxa de Compressão',u'Taxa de Compressão Em Disco','Armazenamento Em Disco']

for file in file_tree:
    filename = file[file.rfind('\\')+1:]
    
    with open(file, encoding="utf8") as arquivo:
        
        #csv_r = csv.reader(arquivo, delimiter=',')
        #if(len(csv_medio)==0):
        #    csv_medio.append(csv_r.fieldnames)
        #for row in csv_r:
        #    print(row)
        
        dataframes.append(pd.read_csv(file))
        

#print(csv_medio)
dataframe_concat = pd.concat(dataframes)

grupo=dataframe_concat.groupby([colunas[0],colunas[1]])


dicionario = []
for g_name in grupo.groups:
    df = grupo.get_group(g_name)
    
    testes, algoritmo = g_name
    m_tempo_exec = df[colunas[2]].mean()
    m_taxa_compressao = df[colunas[3]].mean()
    m_taxa_compressao_disco = df[colunas[4]].mean()
    m_taxa_armazenamento = df[colunas[5]].mean()
    
    dict_row = {
            colunas[0] : testes,
            colunas[1] : algoritmo,
            colunas[2] : m_tempo_exec,
            colunas[3] : m_taxa_compressao,
            colunas[4] : m_taxa_compressao_disco,
            colunas[5] : m_taxa_armazenamento
    }
    #print(dict_row)
    dicionario.append(dict_row)
    #print(testes, algoritmo, m_tempo_exec, m_comparacoes, m_trocas)
    
    #print('###')
    
#print(dicionario)

#cria o dataframe das medias
df_media = pd.DataFrame(dicionario)

#agrupa por algoritmo
group_by_algo = df_media.groupby('Algoritmo')

#extrai o nome dos algoritmos
algo_names = dataframe_concat[colunas[1]].unique()
algo_dfs = []

#separa os dataframes de cada algoritmo
for name in algo_names:
    algo_dfs.append(group_by_algo.get_group(name))

#pega os valores do eixo x (os numeros de teste)
eixo_x = dataframe_concat[colunas[0]].unique()

cores = ['r', 'g--', 'b', 'm', 'c^-', 'y']


#%% Gera a tabela
    
#imprime uma tabela com os dados
    
for i in range(len(algo_dfs)):#algoritmos
    print('\n---',algo_names[i],'---')
    print(str(colunas[0])+', '+str(colunas[2])+' (seg), '+str(colunas[3])+' (%), '+str(colunas[4])+' (%), '+str(colunas[5])+'(kb)')
    for j in range(len(eixo_x)):#testes
        
        testes = list(algo_dfs[i][colunas[0]])[j]
        tempo = list(algo_dfs[i][colunas[2]])[j]
        comp = list(algo_dfs[i][colunas[3]])[j] * 100
        comp_disco = list(algo_dfs[i][colunas[4]])[j] * 100
        taxa_arm = list(algo_dfs[i][colunas[5]])[j] / 1024
        print('%d, %.6f, %.2f, %.2f, %d' % (testes, tempo, comp, comp_disco, taxa_arm))
    



#%% Plota gráficos
    

#plota os resultados do tempo (linear)
for i in range(len(algo_dfs)):
    plt.plot(eixo_x, algo_dfs[i][colunas[2]], cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
plt.ylim(0,4)
plt.xlabel(u"Número de elementos")
plt.ylabel(u"Tempo (segundos)")
plt.title(u"Tempo de Execução")
plt.legend()
plt.savefig("tempoDeExecucao.png")
plt.show()


#plota os resultados da taxa de compressão (linear)
for i in range(len(algo_dfs)):
    plt.plot(eixo_x, algo_dfs[i][colunas[3]]*100, cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
plt.ylim(0,100)
plt.xlabel(u"Número de elementos")
plt.ylabel(u"Taxa de compressão em memória (%)")
plt.title(u"Taxa de Compressão Em Memória")
plt.legend()
plt.savefig("taxaDeCompressaoMemoria.png")
plt.show()

#plota os resultados da taxa de compressão em disco (linear)
for i in range(len(algo_dfs)):
    plt.plot(eixo_x, algo_dfs[i][colunas[4]]*100, cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
plt.ylim(0,100)
plt.xlabel(u"Número de elementos")
plt.ylabel(u"Taxa de compressão em disco (%)")
plt.title(u"Taxa de Compressão Em Disco")
plt.legend()
plt.savefig("taxaDeCompressaoDisco.png")
plt.show()


#plota os resultados da taxa de compressão em disco (linear)
for i in range(len(algo_dfs)):
    plt.plot(eixo_x, algo_dfs[i][colunas[5]]/1024, cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
plt.ylim(0,1500)
plt.xlabel(u"Número de elementos")
plt.ylabel(u"Tamanho do arquivo (kb)")
plt.title(u"Armazenamento compactado em disco")
plt.legend()
plt.savefig("armazenamentoCompactadoEmDisco.png")
plt.show()

'''
#plota os resultados do tempo (log)
for i in range(len(algo_dfs)):
    plt.plot(eixo_x, algo_dfs[i][colunas[2]], cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
plt.xlabel(u"Número de elementos")
plt.ylabel(u"Tempo (segundos)")
plt.title(u"Tempo de Execução")
plt.legend()
plt.yscale('log')
plt.savefig("tempoDeExecucao_log.png")
plt.show()

#plota os resultados do numero de comparações (linear)
for i in range(len(algo_dfs)):
    plt.plot(eixo_x, algo_dfs[i][colunas[4]], cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
plt.xlabel(u"Número de elementos")
plt.ylabel(u"Comparações")
plt.title(u"Número de Comparações")
plt.legend()
plt.savefig("numeroDeComparacoes.png")
plt.show()

#plota os resultados do numero de comparações (log)
for i in range(len(algo_dfs)):
    plt.plot(eixo_x, algo_dfs[i][colunas[4]], cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
plt.xlabel(u"Número de elementos")
plt.ylabel(u"Comparações")
plt.title(u"Número de Comparações")
plt.legend()
plt.yscale('log')
plt.savefig("numeroDeComparacoes_log.png")
plt.show()

#plota os resultados do numero de comparações (linear)
for i in range(len(algo_dfs)):
    plt.plot(eixo_x, algo_dfs[i][colunas[5]], cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
plt.xlabel(u"Número de elementos")
plt.ylabel(u"Colisões")
plt.title(u"Número de Colisões")
plt.legend()
plt.savefig("numeroDeColisoes.png")
plt.show()

#plota os resultados do numero de comparações (linear)
for i in range(len(algo_dfs)):
    plt.plot(eixo_x, algo_dfs[i][colunas[5]], cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
plt.xlabel(u"Número de elementos")
plt.ylabel(u"Colisões")
plt.title(u"Número de Colisões")
plt.legend()
plt.yscale('log')
plt.savefig("numeroDeColisoes_log.png")
plt.show()


#plota os resultados do consumo de memoria (linear)
for i in range(len(algo_dfs)):
    vm = algo_dfs[i][colunas[6]]
    vm /= (1024*1024)
    plt.plot(eixo_x, vm , cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
plt.xlabel(u"Número de elementos")
plt.ylabel(u" Memória usada (Megabytes)")
plt.title(u"Consumo de memória")
plt.legend()
plt.savefig("ConsumoMemoria.png")
plt.show()
'''