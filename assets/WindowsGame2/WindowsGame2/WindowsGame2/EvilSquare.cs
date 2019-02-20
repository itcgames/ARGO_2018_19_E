using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace WindowsGame2
{
    class EvilSquare
    {
        Vector2 evilPos;
        bool alive;  //bool to check if the evil square is alive
        Texture2D evilTexture;
        int speed;  //speed of the evil squares
        int direction; //direction to represent the movement of the evil Squares

        public EvilSquare()
        {

        }
        public void LoadContent(ContentManager theContentManager, string theAssetName)
        {
            evilTexture = theContentManager.Load<Texture2D>("evilSquare");
        }
        public void Draw(SpriteBatch theSpriteBatch)
        {
            theSpriteBatch.Draw(evilTexture, evilPos, Color.White);
        }
        public void Move()
        {

        }
        public void Die()
        {

        }

    }
}
