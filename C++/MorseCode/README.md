# Comment executer le code ?

### - Soit en televersant dans [l'arduino](./arduino/main/)

Le code morse s'affichera dans le moniteur serial et à travers des clignotements.

### - Soit dans le [terminal](./terminal/) avec un compilateur c++

On peut utiliser le compilateur en ligne : [https://www.onlinegdb.com/online_c++_compiler](https://www.onlinegdb.com/online_c++_compiler)  

<br/>
<br/>

## Attention ! Les codes sont différents

J'ai voulu optimiser la vitesse d'exécution sur le terminal mais la mémoire utilisée est énorme pour l'arduino.  
Même si la vitesse n'est pas aussi optimisée, j'ai essayé de reduire au max la mémoire en utilisant des listes de caractères et non pas des String.  

Conclusion:  
Je suis sur que mon code pourrait encore s'améliorer mais il reste tout de même acceptable. Mais le plus important c'est que ça m'a permis d'affiner mes connaissances sur les pointeurs.
