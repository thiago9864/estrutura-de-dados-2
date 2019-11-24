# -*- coding: utf-8 -*-
"""
Created on Fri Aug 16 12:37:11 2019

@author: Thiago
"""
import csv

#arquivos
raiz = 'C:\\Users\\Thiago\\Documents\\Repositorios\\UFJF\estrutura-de-dados-2\\src-trabalho2\\datasets\\'

#raiz = ''

arquivo_game_details = raiz + "originais\\games_detailed_info.csv"
arquivo_game_details_pre = raiz + "preprocessado\\games_detailed_info.csv"

debug = False


#executa preprocessamento para o arquivo de avaliações
#%%

arquivo_pre = open(arquivo_game_details_pre, mode='w', encoding="utf8")
cont = 0

with open(arquivo_game_details, encoding="utf8") as arquivo:

    csv_r = csv.DictReader(arquivo, delimiter=',')
 
    for row in csv_r:
        if(cont>20 and debug==True):
            break

        if(cont==0):
            arquivo_pre.write("id,description\n")
        else:
            id = row['id']
            
            #retira  colchetes da lista de categorias
            description = row['description']
            

            arquivo_pre.write(id + ',' + description + "\n")
        
        cont+=1
        
arquivo_pre.close()