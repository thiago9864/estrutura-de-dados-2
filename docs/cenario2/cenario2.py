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
colunas = ['Teste','Número de Testes','Algoritmo','Tempo de Execução','Número de Comparações','Número de Trocas']

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

grupo=dataframe_concat.groupby([colunas[1],colunas[2]])


dicionario = []
for g_name in grupo.groups:
    df = grupo.get_group(g_name)
    
    testes, algoritmo = g_name
    m_tempo_exec = df[colunas[3]].mean()
    m_comparacoes = df[colunas[4]].mean()
    m_trocas = df[colunas[5]].mean()
    
    dict_row = {
            colunas[1] : testes,
            colunas[2] : algoritmo,
            colunas[3] : m_tempo_exec,
            colunas[4] : m_comparacoes,
            colunas[5] : m_trocas
    }
    #print(dict_row)
    dicionario.append(dict_row)
    #print(testes, algoritmo, m_tempo_exec, m_comparacoes, m_trocas)
    
    #print('###')
    
#print(dicionario)

df_media = pd.DataFrame(dicionario)

group_by_algo = df_media.groupby('Algoritmo')

df_quicksort = group_by_algo.get_group('Quicksort')
df_quicksort_insertion = group_by_algo.get_group('Quicksort Insertion')
df_quicksort_mediana = group_by_algo.get_group('Quicksort Mediana')

plt.plot(df_quicksort[colunas[3]], label=u"Quicksort Recursivo")
#plt.plot(df_quicksort_insertion[colunas[3]], label=u"Quicksort Insertion")
plt.plot(df_quicksort_mediana[colunas[3]], label=u"Quicksort Mediana (k=3)")
plt.legend()
plt.show()