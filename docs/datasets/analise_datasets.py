# -*- coding: utf-8 -*-
"""
Created on Mon Sep 30 17:08:41 2019

@author: Thiago
"""

import pandas as pd


#%% Distribuição normal

file = 'amostra_distr_normal_500000.csv'

csv_distr_norm = pd.read_csv(file)
#print (csv_distr_norm)


df = pd.DataFrame(csv_distr_norm)
hist_distr_norm = df.plot.hist(bins=10, range=[0, 500000], grid=False, color='b', zorder=2, rwidth=1.0)
hist_distr_norm.set_xlabel("Faixa de ids")
hist_distr_norm.set_ylabel("Frequência")
hist_distr_norm.set_title("Distribuição normal com 500000 ids")

print("Qtd de ids unicos", 500000)

#%% Dataset

file = 'amostra_dataset_500000.csv'

csv_dataset = pd.read_csv(file)
#print (csv_dataset)


df = pd.DataFrame(csv_dataset)
hist_dataset = df.plot.hist(bins=100, range=[0, 500000], grid=False, color='b', zorder=2, rwidth=1.0)
hist_dataset.set_xlabel("Faixa de ids")
hist_dataset.set_ylabel("Frequência")
hist_dataset.set_title("Amostra do Dataset com 500000 ids de jogos")


print("Qtd de ids unicos p/ dataset 500000 id", len(df.Id.unique()))

#%% Dataset com id e user convertido pra int somados


file = 'amostra_dataset_id_user_500000.csv'

csv_dataset2 = pd.read_csv(file)
#print (csv_dataset)


df = pd.DataFrame(csv_dataset2)
hist_dataset2 = df.plot.hist(bins=100, range=[0, 500000], grid=False, color='b', zorder=2, rwidth=1.0)
hist_dataset2.set_xlabel("Faixa de ids")
hist_dataset2.set_ylabel("Frequência")
hist_dataset2.set_title(u"Amostra do Dataset com 500000 ids de jogos somados com o user")

print("Qtd de ids unicos p/ dataset 500000 id+user", len(df.Id.unique()))

#%% Dataset com id e user convertido pra int somados


file = 'amostra_dataset_index_500000.csv'

csv_dataset3 = pd.read_csv(file)
#print (csv_dataset)


df = pd.DataFrame(csv_dataset3)
hist_dataset3 = df.plot.hist(bins=100, range=[0, 500000], grid=False, color='b', zorder=2, rwidth=1.0)
hist_dataset3.set_xlabel("Faixa de ids")
hist_dataset3.set_ylabel("Frequência")
hist_dataset3.set_title(u"Amostra do Dataset com 500000 ids de avaliações")

print("Qtd de ids unicos p/ dataset 500000 id+user", len(df.Id.unique()))

