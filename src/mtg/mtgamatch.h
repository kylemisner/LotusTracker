#ifndef MTGAMATCH_H
#define MTGAMATCH_H

#include "../entity/card.h"
#include "../entity/matchinfo.h"
#include "../entity/matchstatediff.h"
#include "../entity/matchplayer.h"
#include "../entity/matchzone.h"
#include "../mtg/mtgcards.h"

#include <QObject>

typedef enum {
    TRANSFER_DRAW,
    TRANSFER_PLAY,
    TRANSFER_DESTROY,
    TRANSFER_EXILE,
    TRANSFER_UNKOWN
} ZoneTransferType;

class MtgaMatch : public QObject
{
    Q_OBJECT
private:
    MtgCards *mtgCards;
    MatchInfo matchInfo;
    MatchPlayer player;
    MatchPlayer opponent;
    QMap<int, MatchZone> zones;
    // objectId, ownerId
    QMap<int, int> stackOwnerTrack;
    // objectId, zoneType
    QMap<int, ZoneType> stackZoneSrcTrack;
    int currentTurn;
    bool playerGoFirst;
    bool resultPlayerWins;
    void updateZones(MatchStateDiff matchStateDiff);
    void updateIdsChanged(MatchStateDiff matchStateDiff);
    void notifyCardZoneChange(int objectId, MatchZone zoneSrc, MatchZone zoneDst,
                              ZoneTransferType zoneTransferType);
    Card* getCardByObjectId(MatchZone zoneDst, int objectId);
    QString getOwnerIdentifier(int objectId, MatchZone zoneSrc);
    ZoneTransferType getZoneTransferType(int objectId, MatchZone zoneSrc, MatchZone zoneDst);

public:
    explicit MtgaMatch(QObject *parent = nullptr, MtgCards *mtgCards = nullptr);
    void startNewMatch(MatchInfo matchInfo);

signals:
    void sgnPlayerDrawCard(Card* card);
    void sgnOpponentDrawCard();
    void sgnPlayerPlayCard(Card* card);
    void sgnOpponentPlayCard(Card* card);

public slots:
    void onMatchInfoSeats(QList<MatchPlayer> players);
    void onMatchInfoResultMatch(int winningTeamId);
    void onSeatIdThatGoFirst(int seatId);
    void onMatchStartZones(QList<MatchZone> zones);
    void onMatchStateDiff(MatchStateDiff matchStateDiff);
    void onNewTurnStarted(int turnNumber);
};

#endif // MTGAMATCH_H
