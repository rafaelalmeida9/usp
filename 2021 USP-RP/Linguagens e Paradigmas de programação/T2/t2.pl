alibi_para_terca(lucas,bernardo).
alibi_para_terca(paulo,bernardo).
alibi_para_terca(luis,lucas).
alibi_para_quinta(alan,lucas).
nao_confiavel(alan).
quer_vinganca(paulo,jean).
quer_vinganca(lucas,jean).
beneficiario(bernardo,jean).
beneficiario(jean,luis).
deve_dinheiro(luis,jean).
deve_dinheiro(lucas,jean).
testemunha_crime(jean,alan).
arma(lucas).
arma(luis).
arma(alan).

interesse_especial(X,Y) :- beneficiario(X,Y) ; deve_dinheiro(X,Y) ; testemunha_crime(Y,X).

quer_matar(X,Y) :- interesse_especial(X,Y) ; quer_vinganca(X,Y).

alibi_aceito(X) :- \+ nao_confiavel(X).

assassino(X) :-  quer_matar(X,jean),arma(X),\+ alibi_para_terca(X,_).

resolver(X):- assassino(X), !.