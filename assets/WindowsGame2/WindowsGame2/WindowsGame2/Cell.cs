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
    class Cell
    {
        Texture2D borderTexture;
        Vector2 borderPos = new Vector2(0, 0);

        public void LoadContent(ContentManager theContentManager, string theAssetName)
        {
            borderTexture = theContentManager.Load<Texture2D>("Border");  
        }

        public void Draw(SpriteBatch theSpriteBatch)
        {
            theSpriteBatch.Draw(borderTexture, borderPos, Color.White);
        }

        public void Update()
        {

        }
    }
}
