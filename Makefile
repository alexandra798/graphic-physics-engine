CC  = $(CXX)

CXXFLAGS = -std=c++11  

# Partie commentée : choisissez les options que vous voulez avoir
#                    en décommentant la/les lignes correspondantes
#
CXXFLAGS += -pedantic -Wall -Wextra -Werror  # 更严格的警告和错误检查
CXXFLAGS += -g                    # pour debugger
# CXXFLAGS += -O2                   # pour optimiser la vitesse


all: testVecteur testIntegrateur1 testPointMateriel

Vecteur.o: Vecteur.cc Vecteur.h

GravitationConstante.o: GravitationConstante.cc GravitationConstante.h ChampForces.h Vecteur.h constantes.h

ObjetMobile.o: ObjetMobile.cc ObjetMobile.h Vecteur.h

PointMateriel.o: PointMateriel.cc PointMateriel.h ObjetPhysique.h Vecteur.h GravitationConstante.h

ObjetPhysique.o: ObjetPhysique.h ObjetMobile.h ChampForces.h Contrainte.h



IntegrateurRungeKutta4.o: IntegrateurRungeKutta4.cc IntegrateurRungeKutta4.h Integrateur.h ObjetMobile.h
IntegrateurEulerCromer.o: IntegrateurEulerCromer.cc IntegrateurEulerCromer.h Integrateur.h ObjetMobile.h

TextViewer.o: TextViewer.cc TextViewer.h SupportADessin.h
Systeme.o: Systeme.cc Systeme.h Dessinable.h ObjetPhysique.h ChampForces.h Contrainte.h Integrateur.h
Libre.o: Libre.cc Libre.h Contrainte.h Vecteur.h



testVecteur.o: testVecteur.cc Vecteur.h
testIntegrateur1.o: testIntegrateur1.cc PointMateriel.h IntegrateurEulerCromer.h
testPointMateriel.o: testPointMateriel.cc PointMateriel.h Vecteur.h ObjetMobile.h ObjetPhysique.h ChampForces.h GravitationConstante.h Contrainte.h Libre.h Integrateur.h IntegrateurEulerCromer.h Dessinable.h SupportADessin.h TextViewer.h




testVecteur: testVecteur.o Vecteur.o
testIntegrateur1: testIntegrateur1.o PointMateriel.o Vecteur.o ObjetMobile.o ObjetPhysique.o GravitationConstante.o   IntegrateurEulerCromer.o
	g++ -o testIntegrateur1 testIntegrateur1.o PointMateriel.o Vecteur.o ObjetMobile.o ObjetPhysique.o  GravitationConstante.o   IntegrateurEulerCromer.o

testPointMateriel: testPointMateriel.o PointMateriel.o Libre.o Vecteur.o ObjetMobile.o ObjetPhysique.o GravitationConstante.o IntegrateurEulerCromer.o TextViewer.o Systeme.o