//
// Created by gabriele on 08/01/26.
//

#ifndef PROGETTOLISTASPESA_UTENTE_H
#define PROGETTOLISTASPESA_UTENTE_H

#include <string>
#include <list>
#include "Observer.h"

class Utente : public Observer{

public:

    Utente(const std::string& nomeUtente, const std::string& pass);

    virtual ~Utente() {}

    std::string getNickname() const;

    std::string getPassword() const;

    // Metodo per il login (restituisce true se nick e pass sono corretti)
    bool login(const std::string& inputNick, const std::string& inputPass) const;

    void modificaNickName(const std::string& nuovoNick);
    void modificaPassword(const std::string& nuovaPass);

    void update() override;

    // Metodi che gestiscono le liste collegate a un utente
    void aggiungiListaPermessa(const std::string& nomeFile);
    const std::list<std::string>& getListePermesse() const;

    // Metodi che servono salvare/caricare gli utenti su/da file
    static bool caricaUtenti(const std::string& nomeFile, std::list<Utente*>& elencoUtenti);
    static bool salvaUtenti(const std::string& nomeFile, const std::list<Utente*>& elencoUtenti);


private:
    std::string nickname;
    std::string password;
    std::list<std::string> listePermesse;
};

#endif //PROGETTOLISTASPESA_UTENTE_H