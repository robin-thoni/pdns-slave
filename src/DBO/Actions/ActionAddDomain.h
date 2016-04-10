//
// Created by robin on 8/9/15.
//

#ifndef PDNS_SLAVE_ACTIONADDDOMAIN_H
#define PDNS_SLAVE_ACTIONADDDOMAIN_H

# include "DBO/Actions/Action.h"

class ActionAddDomain : public Action
{
public:
    ActionAddDomain();

    int getSoaRefresh() const;

    void setSoaRefresh(int soaRefresh);

    int getSoaRetry() const;

    void setSoaRetry(int soaRetry);

    int getSoaExpire() const;

    void setSoaExpire(int soaExpire);

    int getSoaTtl() const;

    void setSoaTtl(int soaTtl);

    int getTtl() const;

    void setTtl(int ttl);

    const std::string &getSoaNs() const;

    void setSoaNs(const std::string &soaNs);

    const std::string &getSoaMail() const;

    void setSoaMail(const std::string &soaMail);

protected:
    const std::string getSql(AbstractSql* sqlDb) const override;

private:
    std::string _soaNs;

    std::string _soaMail;

    int _soaRefresh;

    int _soaRetry;

    int _soaExpire;

    int _soaTtl;

    int _ttl;
};


#endif //PDNS_SLAVE_ACTIONADDDOMAIN_H
