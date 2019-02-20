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
    class AwesomeSquare
    {
        int row;
        int col;
        int score;
        bool alive;
        private int noOfLives;//count for player lives 
        private Texture2D awesomeTexture;
        int direction;
        Vector2 awesomePos;

        private int speed;//speed of the player is set 
        public string assetName;


        public AwesomeSquare(int size)
        {

            awesomePos = new Vector2(size, size);
        }

        public void Draw(SpriteBatch theSpriteBatch)
        {
            
            theSpriteBatch.Draw(awesomeTexture, awesomePos, Color.White);
        }
        public void LoadContent(ContentManager theContentManager, string theAssetName)
        {
            awesomeTexture = theContentManager.Load<Texture2D>("awesomeSquare");
            assetName = theAssetName;
        }
        public void PlayerKick()//what happens when the player kicks a world square
        {
            
        }
        public void MoveUp()
        {
            awesomePos.Y = awesomePos.Y - awesomeTexture.Height;
        }
        public void MoveDown()
        {
            awesomePos.Y = awesomePos.Y + awesomeTexture.Height;
        }
        public void MoveLeft()
        {
            awesomePos.X = awesomePos.X - awesomeTexture.Width;
        }
        public void MoveRight()
        {
            awesomePos.X = awesomePos.X + awesomeTexture.Width;
        }
        
        public Texture2D AwesomeTexture
        {
            get { return awesomeTexture; }
            set { awesomeTexture = value; }
        }

        public float Xposition
        {
            get { return awesomePos.X; }
            set { awesomePos.X = value; }
        }

        public float Yposition
        {
            get { return awesomePos.Y; }
            set { awesomePos.Y = value; }
        }
    }
}
