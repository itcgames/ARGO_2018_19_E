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
    class WorldSquare
    {
        bool alive = true; // bool if the world Square is alive
        int maxRows = 12;
        int maxCols = 12;
        int speed; //speed of movement of the world square
        Texture2D worldTexture;
        Texture2D noTexture;
        Vector2 worldPos = new Vector2(0,0);
        int row;
        int col;

        public WorldSquare(int width, int height)
        {
            worldPos = new Vector2(width, height);
        }

        public void LoadContent(ContentManager theContentManager, string theAssetName)
        {
            worldTexture = theContentManager.Load<Texture2D>("worldSquare");
            noTexture = theContentManager.Load<Texture2D>("noTexture");
           
        }

        public void Draw(SpriteBatch theSpriteBatch)
        {
            theSpriteBatch.Draw(worldTexture, worldPos, Color.White); 
        }

        public void Move(int viewportWidth, int viewportHeight)
        {
            
        }


        public Vector2 WorldVec
        {
            get { return worldPos; }
            set { worldPos = value; }
        }

        public Texture2D WorldTexture
        {
            get { return worldTexture; }
            set { worldTexture = value; }
        }

        public bool NotAlive
        {
            get { return alive; }
            set { alive = value; }
        }
    }
}
