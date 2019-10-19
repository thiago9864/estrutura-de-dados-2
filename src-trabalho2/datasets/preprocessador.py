# -*- coding: utf-8 -*-
"""
Created on Fri Aug 16 12:37:11 2019

@author: Thiago
"""
import csv

#arquivos
raiz = 'C:\\Users\\Thiago\\Documents\\Repositorios\\UFJF\estrutura-de-dados-2\\src\\datasets\\'

#raiz = ''

arquivo_reviews = raiz + "originais\\bgg-13m-reviews.csv"
arquivo_reviews_pre = raiz + "preprocessado\\bgg-13m-reviews.csv"

arquivo_game_details = raiz + "originais\\games_detailed_info.csv"
arquivo_game_details_pre = raiz + "preprocessado\\games_detailed_info.csv"

arquivo_users_rated = raiz + "originais\\2019-05-02.csv"
arquivo_users_rated_pre = raiz + "preprocessado\\2019-05-02.csv"


debug = False

#executa preprocessamento para o arquivo de avaliações
#%%

arquivo_pre = open(arquivo_reviews_pre, mode='w', encoding="utf8")
cont = 0
id_list = []#lista pra armazenar os ids já escritos

with open(arquivo_reviews, encoding="utf8") as arquivo:

    csv_r = csv.reader(arquivo, delimiter=',')
 
    for row in csv_r:
        if(cont>20 and debug==True):
            break
        
        if(debug):
            print(row)

        if(cont==0):
            arquivo_pre.write("id,user,rating\n")
        else:
            
            id = row[0]#id registro. O row[4] é o id do jogo
            user = row[1].replace(',','&comma;')
            rating = row[2]
            
            #só salva chaves unicas no arquivo preprocessado
            #if(id not in id_list):
            #    arquivo_pre.write(id + ',' + user + ',' + rating + "\n")
            #    id_list.append(id)
            
            arquivo_pre.write(id + ',' + user + ',' + rating + "\n")
            id_list.append(id)
            
        cont+=1
        
arquivo_pre.close()


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
            arquivo_pre.write("id,boardgamecategory\n")
        else:
            id = row['id']
            
            #retira  colchetes da lista de categorias
            boardgamecategory = row['boardgamecategory'].strip('[').strip(']')
            
            #retira as aspas
            boardgamecategory = boardgamecategory.replace("'","")
            
            #quebra em uma lista
            categorias = boardgamecategory.split(',')
            
            #monta uma string separada por ; das categorias
            str_categorias = ""
            for c in categorias:
                if(str_categorias != ""):
                    str_categorias += "|"
                str_categorias += c.strip(' ').replace(',','&comma;')

            arquivo_pre.write(id + ',' + str_categorias + "\n")
        
        cont+=1
        
arquivo_pre.close()

#executa preprocessamento para o arquivo users rated
#%%


arquivo_pre = open(arquivo_users_rated_pre, mode='w', encoding="utf8")
cont = 0

with open(arquivo_users_rated, encoding="utf8") as arquivo:

    csv_r = csv.reader(arquivo, delimiter=',')
 
    for row in csv_r:
        if(cont>20 and debug==True):
            break

        if(cont==0):
            arquivo_pre.write("id,Users rated\n")
        else:
            id = row[0]
            users_rated = row[6]

            arquivo_pre.write(id + ',' + users_rated + "\n")
        cont+=1
        
arquivo_pre.close()

#%%
