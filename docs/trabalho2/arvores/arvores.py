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
colunas = [u'Número de Testes','Algoritmo',u'Tempo de Execução',u'Número de Comparações',u'Número de Copias']

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
    m_num_comparacao = df[colunas[3]].mean()
    m_num_copias = df[colunas[4]].mean()
    
    dict_row = {
            colunas[0] : testes,
            colunas[1] : algoritmo,
            colunas[2] : m_tempo_exec,
            colunas[3] : m_num_comparacao,
            colunas[4] : m_num_copias
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
    print(str(colunas[0])+', '+str(colunas[2])+' (seg), '+str(colunas[3])+', '+str(colunas[4]))
    for j in range(len(eixo_x)):#testes
        
        testes = int(list(algo_dfs[i][colunas[0]])[j])
        tempo = float(list(algo_dfs[i][colunas[2]])[j])
        comp = int(list(algo_dfs[i][colunas[3]])[j])
        copias = int(list(algo_dfs[i][colunas[4]])[j])
        print('%d & %.6f & %d & %d' % (testes, tempo, comp, copias))
    



#%% Plota gráficos
    

#plota os resultados do tempo (linear)
for i in range(len(algo_dfs)):
    plt.plot(eixo_x, algo_dfs[i][colunas[2]], cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
plt.ylim(0,2.5)
plt.xlabel(u"Número de elementos")
plt.ylabel(u"Tempo (segundos)")
plt.title(u"Tempo de Execução")
plt.legend()
plt.savefig("tempoDeExecucao.png")
plt.show()


#plota os resultados da taxa de compressão (linear)
for i in range(len(algo_dfs)):
    plt.plot(eixo_x, algo_dfs[i][colunas[3]], cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
#plt.ylim(0,100)
plt.xlabel(u"Número de elementos")
plt.ylabel(u"Comparações")
plt.title(u"Número de Comparações")
plt.legend()
plt.savefig("numeroDeComparacoes.png")
plt.show()


#plota os resultados da taxa de compressão (linear)
for i in range(len(algo_dfs)):
    plt.plot(eixo_x, algo_dfs[i][colunas[4]], cores[i], label=algo_names[i])

#plt.xticks(eixo_x)
#plt.ylim(0,100)
plt.xlabel(u"Número de elementos")
plt.ylabel(u"Cópias")
plt.title(u"Número de Cópias")
plt.legend()
plt.savefig("numeroDeCopias.png")
plt.show()

