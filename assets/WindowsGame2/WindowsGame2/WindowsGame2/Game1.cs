using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace WindowsGame2
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;

        Cell[] border;
        AwesomeSquare awesomeSquare;
        WorldSquare[,] maze;
        EvilSquare[] evilSquares;
        int MaxCols = 13;
        int MaxRows = 13;
        int MaxEvil = 3;
        const int size = 30;
        bool gameOver;
        Random rndNumber;
        KeyboardState keyLast;

        int viewportHeight;
        int viewportWidth;

        int height = 30;
        int width = 30;
        int x = 0;
        int y = 0;
        
        
        

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";

            maze = new WorldSquare[MaxRows, MaxCols];
            border = new Cell[MaxCols];
            

            graphics.PreferredBackBufferHeight = 360;
            graphics.PreferredBackBufferWidth = 360;
    
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            
            // TODO: Add your initialization logic here
            awesomeSquare = new AwesomeSquare(size);

            for (int index = 0; index < MaxEvil; index++)
            {
                evilSquares[index] = new EvilSquare();
            }

            for (int row = 0; row < MaxRows; row++)
            {
                for (int col = 0; col < MaxCols; col++)
                {
                    maze[row, col] = new WorldSquare(x, y);

                    y = y + height;

                }
                y = 0;
                x = x + width;

            }
            maze[2, 2].NotAlive = false;
            maze[3, 2].NotAlive = false;
            maze[4, 2].NotAlive = false;
            maze[6, 2].NotAlive = false;
            maze[7, 2].NotAlive = false;
            maze[8, 2].NotAlive = false;
            maze[8, 3].NotAlive = false;
            maze[8, 4].NotAlive = false;
            maze[8, 5].NotAlive = false;
            maze[8, 6].NotAlive = false;
            maze[8, 7].NotAlive = false;
            maze[8, 8].NotAlive = false;
            maze[8, 9].NotAlive = false;
            maze[9, 9].NotAlive = false;
            maze[2, 3].NotAlive = false;
            maze[2, 4].NotAlive = false;
            maze[2, 5].NotAlive = false;
            maze[2, 6].NotAlive = false;
            maze[2, 7].NotAlive = false;
            maze[2, 8].NotAlive = false;
            maze[2, 9].NotAlive = false;
            maze[3, 6].NotAlive = false;
            maze[4, 6].NotAlive = false;
            maze[5, 6].NotAlive = false;
            maze[1, 5].NotAlive = false;
            maze[3, 9].NotAlive = false;
            maze[4, 9].NotAlive = false;
            maze[5, 9].NotAlive = false;
            maze[6, 9].NotAlive = false;
            maze[7, 9].NotAlive = false;
            maze[7, 10].NotAlive = false;

            for (int index = 0; index < MaxCols; index++)
            {
                maze[index, 0].NotAlive = false;
                maze[index, 11].NotAlive = false;
                maze[0, index].NotAlive = false;
                maze[11, index].NotAlive = false;
                y = y + height;
            }

            
            viewportWidth = graphics.GraphicsDevice.Viewport.Width;
            viewportHeight = graphics.GraphicsDevice.Viewport.Height;

            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);

            // TODO: use this.Content to load your game content here
            for (int row = 0; row < MaxRows; row++)
            {
                for(int col = 0; col < MaxCols; col++)
                {
                    maze[row,col].LoadContent(this.Content, "worldSquare");
                }
            }
            for (int index = 0; index < MaxEvil; index++)
            {
                evilSquares[index].LoadContent(this.Content, "evilSquare");
            }
            awesomeSquare.LoadContent(this.Content, "awesomeSquare");
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            // Allows the game to exit
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
                this.Exit();

            
            KeyboardState keyCurrent = Keyboard.GetState();
            

            // TODO: Add your update logic here
            for (int row = 0; row < MaxRows; row++)
            {
                for (int col = 0; col < MaxCols; col++)
                {
                    maze[row, col].Move(viewportWidth, viewportHeight);          
                }

            }

            for (int index = 0; index < MaxEvil; index++)
            {
                evilSquares[index].Move();
            }


            if (keyCurrent.IsKeyDown(Keys.Left) && keyLast.IsKeyUp(Keys.Left) && awesomeSquare.Xposition > 0)
            {
                awesomeSquare.MoveLeft();
            }
            if (keyCurrent.IsKeyDown(Keys.Right) & keyLast.IsKeyUp(Keys.Right) && awesomeSquare.Xposition + awesomeSquare.AwesomeTexture.Width < viewportWidth)
            {
                awesomeSquare.MoveRight();
            }
            if (keyCurrent.IsKeyDown(Keys.Up) && keyLast.IsKeyUp(Keys.Up) && awesomeSquare.Yposition > 0)
            {
                awesomeSquare.MoveUp();
            }
            if (keyCurrent.IsKeyDown(Keys.Down) && keyLast.IsKeyUp(Keys.Down) && awesomeSquare.Yposition + awesomeSquare.AwesomeTexture.Height < viewportHeight)
            {
                awesomeSquare.MoveDown();
            }

            keyLast = keyCurrent;
            

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {

            spriteBatch.Begin();

            GraphicsDevice.Clear(Color.CornflowerBlue);

            // TODO: Add your drawing code here
            
            for (int row = 0; row < MaxRows; row++)
            {
                
                for (int col = 0; col < MaxCols; col++)
                {
                    if (maze[row, col].NotAlive == !true)
                    {
                        maze[row, col].Draw(this.spriteBatch);
                    }
                }   
                
            }
            for (int index = 0; index < MaxEvil; index++)
            {
                evilSquares[index].Draw(this.spriteBatch);
            }
            
            awesomeSquare.Draw(this.spriteBatch);

            spriteBatch.End();

            base.Draw(gameTime);
        }
    }
}
