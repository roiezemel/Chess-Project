using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace chessGraphics
{
    public partial class Form1 : Form
    {
        private Square srcSquare;
        private Square dstSquare;

        private pipe enginePipe;
        Button[,] matBoard;

        bool isCurPlWhite = true;
        bool isGameOver = false;
        string promoteBoard = null;
        bool skip = false;

        const int BOARD_SIZE = 8;

        public Form1()
        {
            this.BackColor = Color.FromArgb(0, 0, 0); // this should be pink-ish

            InitializeComponent();
        }

        private void initForm()
        {
            enginePipe.connect();

            Invoke((MethodInvoker)delegate {  

                lblWaiting.Visible = false;
                lblCurrentPlayer.Visible = true;
                label1.Visible = true;


                string s = enginePipe.getEngineMessage();

                if (s.Length != (BOARD_SIZE * BOARD_SIZE + 1))
                {
                    MessageBox.Show("The length of the board's string is not according the PROTOCOL");
                    this.Close();

                }
                else
                {
                    isCurPlWhite = (s[s.Length - 1] == '0');
                    paintBoard(s, true);
                }

            });
    
        }

        Thread connectionThread;
        private void Form1_Load(object sender, EventArgs e)
        {
            enginePipe = new pipe();
            //this.Show();
            
            //MessageBox.Show("Press OK to start waiting for engine to connect...");
            connectionThread = new Thread(initForm);
            connectionThread.Start();
            connectionThread.IsBackground = true;
            
            //initForm();
        
        }

        Image getImageBySign(char sign)
        {
            switch (sign)
            {
                case 'q':
                    return Properties.Resources.q_black;
                case 'Q':
                    return Properties.Resources.q_white;
                case 'k':
                    return Properties.Resources.k_black;
                case 'K':
                    return Properties.Resources.k_white;
                case 'p':
                    return Properties.Resources.p_black;
                case 'P':
                    return Properties.Resources.p_white;
                case 'r':
                    return Properties.Resources.r_black;
                case 'R':
                    return Properties.Resources.r_white;
                case 'n':
                    return Properties.Resources.n_black;
                case 'N':
                    return Properties.Resources.n_white;
                case 'b':
                    return Properties.Resources.b_black;
                case 'B':
                    return Properties.Resources.b_white;
                case '#':
                    return null;
                default:
                    return Properties.Resources.x;

            }
        }

        private void paintBoard(string board, bool createBoard)
        {
            int i, j, z=0;

            if (createBoard)
                matBoard = new Button[BOARD_SIZE, BOARD_SIZE];

            btnBoard.FlatAppearance.MouseOverBackColor = Color.LightGray;
            
            Button newBtn;
            Point pnt;

            int currentWidth = btnBoard.Location.X;
            int currentHeight = btnBoard.Location.Y;
            
            bool isColBlack = true;
            bool isRowBlack = false ;
            
            this.SuspendLayout();

            lblCurrentPlayer.Text = isCurPlWhite ? "White" : "Black";

            for (i = 0; i < BOARD_SIZE; i++)
            {
                currentWidth = btnBoard.Location.X;
                isColBlack = isRowBlack;

                for (j = 0; j < BOARD_SIZE; j++)
                {

                    if (!createBoard)
                        Controls.Remove(matBoard[i, j]);
                    newBtn = new Button();
                    matBoard[i, j] = newBtn;

                    newBtn.FlatAppearance.MouseOverBackColor = btnBoard.FlatAppearance.MouseOverBackColor ;
                    newBtn.BackColor = isColBlack ? Color.Gray : Color.White;
                    newBtn.FlatAppearance.BorderColor = btnBoard.FlatAppearance.BorderColor;
                    newBtn.FlatAppearance.BorderSize = btnBoard.FlatAppearance.BorderSize;
                    newBtn.FlatStyle = btnBoard.FlatStyle;

                    newBtn.Size = new System.Drawing.Size(btnBoard.Width, btnBoard.Height);
                    newBtn.Tag = new Square(i, j);
                    pnt = new Point(currentWidth, currentHeight );
                    newBtn.Location = pnt;
                    newBtn.BackgroundImageLayout = ImageLayout.Stretch;

                    newBtn.BackgroundImage  = getImageBySign(board[z]);
                    
                    newBtn.Click += lastlbl_Click;

                    Controls.Add(newBtn);


                    currentWidth += btnBoard.Width;
                    isColBlack = !isColBlack;
                    z++;

                }

                isRowBlack = !isRowBlack;
                currentHeight += btnBoard.Height;

            }

            Controls.Remove(btnBoard);
            this.ResumeLayout(false);
        }

        void lastlbl_Click(object sender, EventArgs e)
        {
            
            if (promoteBoard != null) {
                lastlbl_Click_forPromotion(sender, e);
                return;
            }

            Button b = (Button)sender;

            if (srcSquare != null)
            {
                // unselected
                if (matBoard[srcSquare.Row, srcSquare.Col] == b)
                {
                 
                    matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Black;
                    srcSquare = null;
                }
                else
                {
                    dstSquare = (Square)b.Tag;
                    matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.DarkGreen;

                    Thread t = new Thread(playMove);
                    t.Start();
                 //   t.IsBackground = true;
                    //playMove();
                }
            }
            else
            {
                srcSquare = (Square)b.Tag;
                matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.DarkGreen;
            }
         
        }

        // messages should be according the protocol.
        // index is the message number in the protocol
        string[] messages =  {
            "Valid move",
            "Valid move - you made chess",
            "Invalid move - not your player",
            "Invalid move - destination is not free",
            "Invalid move - chess wil occure",
            "Invalid move - out of bounds",
            "Invalid move - illegeal movement with piece",
            "Invalid move - source and dest are equal",
            "Game over - check mate",
            "Unknown message"
            };


        string convertEngineToText(string m)
        {
            int res;
            bool b = int.TryParse(m, out res);

            if (!b || res < 0 || res >= messages.Length)
                return messages[messages.Length - 1];

            return messages[res];
        }
        


        void playMove()
        {
            if (isGameOver)
                return;
           

            try
            {
                
                 Invoke((MethodInvoker)delegate {
                     int code = 0;
                     string res = null;
                     if (!skip)
                     {
                         lblEngineCalc.Visible = true;

                         lblMove.Text = string.Format("Move from {0} to {1}", srcSquare, dstSquare);
                         lblMove.Visible = true;
                         //lblEngineCalc.Invalidate();

                         label2.Visible = false;
                         lblResult.Visible = false;

                         this.Refresh();


                         // should send pipe to engine
                         enginePipe.sendEngineMove(srcSquare.ToString() + dstSquare.ToString());


                         // should get pipe from engine
                         string m = enginePipe.getEngineMessage();

                         if (!enginePipe.isConnected())
                         {
                             MessageBox.Show("Connection to engine has lost. Bye bye.");
                             this.Close();
                             return;
                         }
                         bool special = false;
                         String after = null;

                         if (m.Length > 1)
                         {
                             after = m.Substring(1);
                             m = m.Substring(0, 1);
                             if (after.Length > 10)
                             {
                                 promoteBoard = after.Substring(0, after.Length - 1);
                                 //bool isWhite = 0 != after[0] - '0';
                             }
                         }
                         code = m[0] - '0';

                         res = convertEngineToText(m);

                         if (res.ToLower().StartsWith("game over"))
                         {
                             isGameOver = true;
                         }
                         if (res.ToLower().StartsWith("valid") || isGameOver)
                         {
                             isCurPlWhite = !isCurPlWhite;
                             lblCurrentPlayer.Text = isCurPlWhite ? "White" : "Black";

                             if (!special)
                             {
                                 matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                                 matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage = null;
                             }

                             matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Black;
                             matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.Black;

                         }

                         this.Refresh();


                         if (promoteBoard != null)
                         {
                             bool isWhite = true;
                             string pawnPro = isWhite ? "##########################################################RNBQ##" : "##########################################################rnbq##";
                             paintForPromotion(pawnPro);
                             this.Refresh();
                             skip = true;
                             return;
                         }
                         else if (after != null)
                         {
                             int x1 = after[0] - '0';
                             int y1 = after[1] - '0';
                             int x2 = after[2] - '0';
                             int y2 = after[3] - '0';
                             matBoard[y2, x2].BackgroundImage = matBoard[y1, x1].BackgroundImage;
                             matBoard[y1, x1].BackgroundImage = null;
                         }


                         this.Refresh();
                     }
                     else
                     {
                         skip = false;
                     }
                     
                     if (code < 2) {
                         this.SuspendLayout();

                         string msg = enginePipe.getEngineMessage();

                         this.ResumeLayout(false);

                         int x1 = msg[1] - '0';
                         int y1 = msg[2] - '0';
                         int x2 = msg[3] - '0';
                         int y2 = msg[4] - '0';
                         msg = msg.Substring(0, 1);
                         res = convertEngineToText(msg);

                         if (res.ToLower().StartsWith("game over"))
                         {
                             isGameOver = true;
                         }

                         matBoard[y2, x2].BackgroundImage = matBoard[y1, x1].BackgroundImage;
                         matBoard[y1, x1].BackgroundImage = null;

                         isCurPlWhite = !isCurPlWhite;
                         lblCurrentPlayer.Text = isCurPlWhite ? "White" : "Black";
                     }

                     lblEngineCalc.Visible = false;
                    lblResult.Text = string.Format("{0}", res);
                    lblResult.Visible = true;
                    label2.Visible = true;
                    this.Refresh();
                 });
                
           
                }
                catch
                {

                }
                finally
                {
                        Invoke((MethodInvoker)delegate
                    {
                        if (srcSquare != null)
                            matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Black;

                        if (dstSquare != null)
                            matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.Black;
                        if (!skip)    
                            dstSquare = null;
                        srcSquare = null;

                    });
                }

        }
        void paintForPromotion(string board)
        {
            int i = 0, j = 0, z = 0;
            for (i = 0; i < BOARD_SIZE; i ++)
            {
                for(j = 0; j < BOARD_SIZE; j++)
                {
                    Button newBtn = matBoard[i, j];
                    newBtn.BackgroundImage = getImageBySign(board[z]);
                    z++;
                }
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
   

            enginePipe.sendEngineMove("quit");
            enginePipe.close();
        }
        void lastlbl_Click_forPromotion(object sender, EventArgs e)
        {
            Button b = (Button)sender;

            for (int j = 2; j <= 5; j++) {
                if (matBoard[7, j] == b) {

                    Image im = matBoard[7, j].BackgroundImage;
                    
                    paintForPromotion(promoteBoard);
                    
                    matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = im;
                    dstSquare = null;
                    promoteBoard = null;
                    enginePipe.sendEngineMove((j - 2) + "");
                    Thread t = new Thread(playMove);
                    t.Start();
                    return;
                }
            }

        }

        

    }
}

