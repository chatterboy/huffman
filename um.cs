#define NOMY
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
#if NOMY
using System.Data.Sql;
using System.Data.SqlClient;
#else
using MySql.Data;
using MySql.Data.MySqlClient;
#endif

namespace AIIB
{
    public partial class ProblemDetail : Form
    {
#if NOMY
        SqlConnection conn = new SqlConnection("server=localhost; user=root; password=1234; database=ibm");
#else
        MySqlConnection conn = new MySqlConnection("server=localhost; user=root; password=1234; database=ibm");
#endif
        WebBrowser wb;

        public ProblemDetail()
        {
            InitializeComponent();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void saveBtn_Click(object sender, EventArgs e)
        {
            this.Hide();
            Professor form4 = new Professor();
            form4.Show();
        }

        private void ProblemDetail_Load(object sender, EventArgs e)
        {

        
        }
        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            System.Windows.Forms.HtmlDocument document = this.wb.Document;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            conn.Open();
            string sql = "SELECT count (*) FROM problems";
            // db에 문제가 몇 개가 있는가?
#if NOMY
            SqlCommand cmd = new SqlCommand(sql, conn);
#else
            MySqlCommand cmd = new MySqlCommand(sql, conn);
#endif
            int n = Convert.ToInt32(cmd.ExecuteScalar());
            // [1,|문제수|] 수 중 랜덤하게 하나 선택
            Random rd = new Random();
            int i = rd.Next(1, n);
            // 선택된 수 i에 대해서 문제번호가 i인 문제의 레코드를 가져옴
            sql = "SELECT html, correct, type, nocorrect, noincorrect FROM problems";
            // 출력
#if NOMY
            cmd = new SqlCommand(sql, conn);
            SqlDataReader rdr = cmd.ExecuteReader();
#else
            cmd = new MySqlCommand(sql, conn);
            MySqlDataReader rdr = cmd.ExecuteReader();
#endif
//            WebBrowser.DocumentText = "<P CLASS=HStyle2><SPAN STYLE='font-size:13.3pt;;font-weight:\"bold\";font-style:\"italic\";line-height:145%;'></SPAN>(A), (B), (C)의 각 네모 안에서 어법에 맞는 표현으로 가장 적절한 것은? </P> <P CLASS=HStyle3 STYLE='line-height:140%;'>Albert Einstein talked about what influenced his life as a scientist. He remembered seeing a pocket compass when he was five years old and (A) <span style=\"border:1px solid\">marveling/marveled</span> that the needle always pointed north. In that moment, Einstein recalled, he “felt something deeply hidden behind things.” Around the age of six, Einstein began studying the violin. When after several years he recognized the mathematical structure of music, the violin became a lifelong friend of his. When Einstein was ten, his family enrolled him in the Luitpold Gymnasium, (B) <span style=\"border:1px solid\">there/where</span> he developed a suspicion of authority. The trait served Einstein well later in life as a scientist. His habit of skepticism made (C) <span style=\"border:1px solid\">him/it</span> easy to question many long<SPAN STYLE=';'>?</SPAN>standing scientific assumptions.</P> <P CLASS=HStyle6>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(A)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; (B)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; (C)</P> <P CLASS=HStyle7>① marveling<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN>there<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN>him</P> <P CLASS=HStyle7>② marveled<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN>there<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN>him</P> <P CLASS=HStyle7>③ marveling<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN>where<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN>him</P> <P CLASS=HStyle7>④ marveled<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN>where<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN>it</P> <P CLASS=HStyle7>⑤ marveling<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN>where<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN>it</P>";
            wb = new WebBrowser();
            wb.DocumentText = "<P CLASS=HStyle2><SPAN STYLE='font-size:13.3pt;;font-weight:\"bold\";font-style:\"italic\";line-height:145%;'></SPAN>(A), (B), (C)의 각 네모 안에서 어법에 맞는 표현으로 가장 적절한 것은? </P> <P CLASS=HStyle3 STYLE='line-height:140%;'>Albert Einstein talked about what influenced his life as a scientist. He remembered seeing a pocket compass when he was five years old and (A) <span style=\"border:1px solid\">marveling/marveled</span> that the needle always pointed north. In that moment, Einstein recalled, he “felt something deeply hidden behind things.” Around the age of six, Einstein began studying the violin. When after several years he recognized the mathematical structure of music, the violin became a lifelong friend of his. When Einstein was ten, his family enrolled him in the Luitpold Gymnasium, (B) <span style=\"border:1px solid\">there/where</span> he developed a suspicion of authority. The trait served Einstein well later in life as a scientist. His habit of skepticism made (C) <span style=\"border:1px solid\">him/it</span> easy to question many long<SPAN STYLE=';'>?</SPAN>standing scientific assumptions.</P> <P CLASS=HStyle6>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(A)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; (B)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; (C)</P> <P CLASS=HStyle7>① marveling<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN>there<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN>him</P> <P CLASS=HStyle7>② marveled<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN>there<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN>him</P> <P CLASS=HStyle7>③ marveling<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN>where<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN>him</P> <P CLASS=HStyle7>④ marveled<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN>where<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN>it</P> <P CLASS=HStyle7>⑤ marveling<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;</SPAN>where<SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</SPAN><SPAN style='HWP-TAB:1;'>&nbsp;&nbsp;&nbsp;</SPAN>it</P>";
        }

    }
}
