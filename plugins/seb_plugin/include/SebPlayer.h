#ifndef Header_qcore_SebPlayer
#define Header_qcore_SebPlayer

#include "Player.h"

namespace qplugin
{
   class SebPlayer : public qcore::Player
   {
   public:

      /** Construction */
      SebPlayer(qcore::PlayerId id, const std::string& name, qcore::GamePtr game);

      /** Defines player's behavior. In this particular case, it's a really dummy one */
      void doNextMove() override;
   };
}

#endif // Header_qcore_SebPlayer
