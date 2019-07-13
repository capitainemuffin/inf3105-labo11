/*  INF3105 - Structures de données et algorithmes
    Lab 11 -- Graphes / Représentations et algorithmes de base
    http://ericbeaudry.uqam.ca/INF3105/lab11/
*/
#if !defined(__GRAPHE_H__)
#define __GRAPHE_H__

#include <queue>
#include <map>
#include <set>
#include <iostream>

using namespace std;

// Le type S est le type utilisé pour identifier les sommets
template <class S>
class Graphe{
  public:
    // Interface public pour créer le graphe.
    void ajouterSommet(const S& s);
    void ajouterAreteOrientee(const S& s1, const S& s2);
    void ajouterAreteNonOrientee(const S& s1, const S& s2);

    // Interface public pour les requêtes de base.
    // Amélioration possible : retourner le résultat au lieu de faire l'affichage à l'interne.
    void parcoursRechercheProfondeur(const S& s) const;
    void parcoursRechercheProfondeur2(const S& s) const;
    void parcoursRechercheLargueur(const S& s) const;
    void extraireCompostantesConnexes() const;

  private:
    struct Sommet{
        mutable bool visite;
        S sommet;
        set<S> voisins; // ensemble des sommets accessibles via les arêtes sortantes du sommet.
                        // Cela est légèrement différent de la page 120 des notes de cours.
                        // C'est voulu, car ici les arêtes ne sont pas étiquetées par un poids (ex: distance).
                        // Pour attacher une étiquette, il suffirait de modifier pour : map<S, A> sortants;
    };


    map<S, Sommet> sommets; // identification --> sommet
};

template <class S>
void Graphe<S>::ajouterSommet(const S& s){
    this->sommets[s];
}

template <class S>
void Graphe<S>::ajouterAreteNonOrientee(const S& s1, const S& s2){
    // Doit ajouter les 2 arêtes orientées : s1->s2 et s2->s1;
    this->sommets[s1].voisins.insert(s2);
    this->sommets[s2].voisins.insert(s1);
}

template <class S>
void Graphe<S>::ajouterAreteOrientee(const S& s1, const S& s2){
    // À compléter.
    // Doit uniquement ajouter s1->s2.
    this->sommets[s1].voisins.insert(s2);
}

template <class S>
void Graphe<S>::parcoursRechercheProfondeur(const S& s) const{

    for(auto& sommet : this->sommets){
        sommet.second.visite = false;
    }

    parcoursRechercheProfondeur2(s);
    cout << endl;
}

template<class S> void Graphe<S>::parcoursRechercheProfondeur2(const S& s) const {

    const Sommet& sommet = this->sommets.at(s);
    sommet.visite = true;
    cout << s << " ";

    for(auto& voisin : sommet.voisins){

        const Sommet& sommet_voisin = this->sommets.at(voisin);

        if(!sommet_voisin.visite){

            parcoursRechercheProfondeur2(voisin);

        }

    }
    
}

template <class S>
void Graphe<S>::parcoursRechercheLargueur(const S& s) const{

    queue<S> file;
    file.push(s);

    for(auto& sommet : this->sommets){
        sommet.second.visite = false;
    }

    while(!file.empty()){

        cout << file.front() << " ";

        const Sommet& sommet = this->sommets.at(file.front());
        sommet.visite = true;
        file.pop();

        for(auto& voisin : sommet.voisins) {

            const Sommet& sommet_voisin = this->sommets.at(voisin);

            if(!sommet_voisin.visite){
                sommet_voisin.visite = true;
                file.push(voisin);  
            } 
            
        }

    }

    cout << endl;
}

template <class S>
void Graphe<S>::extraireCompostantesConnexes() const{
    // À compléter.
    // Ne faites que l'extraction simple en premier (plus simple que l'extraction de composantes *fortement* connexes).
}

#endif

