#include "SebPlayer.h"
#include "QcoreUtil.h"

#include <thread>

using namespace qcore::literals;
using namespace std::chrono_literals;

namespace qplugin
{
   /** Log domain */
   const char * const DOM = "qplugin::SEB";

   SebPlayer::SebPlayer(qcore::PlayerId id, const std::string& name, qcore::GamePtr game) :
      qcore::Player(id, name, game)
   {
   }

   /** Defines player's behavior. In this particular case, it's a really dummy one */
   void SebPlayer::doNextMove()
   {
      LOG_INFO(DOM) << "Player " << (int)getId() << " is thinking..";

      // do random move
      move(qcore::Direction::Down) or move(qcore::Direction::Left) or move(qcore::Direction::Right) or move(qcore::Direction::Up);
   }

} // namespace qplugin
