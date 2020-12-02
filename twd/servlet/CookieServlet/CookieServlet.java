import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class CookieServlet extends HttpServlet{
    private String values[] = { "doki-doki", "cyber-punk", 
                                "squadrons", "fortnite", "MTGA" };

    private String links[] = { "steam.com/doki-doki", "steam.com/cyberpunk-2077", 
                                "steam.com/squadrons", "steam.com/fortnite", "steam.com/MTGA" };

    private int maxAge = 60; // Cookie living time    
    
    private String getLink(String game) {
        for(int i=0; i<values.length; i++)
            if( game.equals(values[i]) )
                return links[i];
        
        return "";
    }
    
    public void doPost(HttpServletRequest request,
                        HttpServletResponse response) 
        throws ServletException, IOException
    {
        PrintWriter output;
        String game = request.getParameter( "game" );

        Cookie cookie = new Cookie(game, getLink(game));

        cookie.setMaxAge( maxAge);
        response.addCookie(cookie);

        response.setContentType("text/html");
        output = response.getWriter();

        output.println("<html><head><title>");
        output.println("Cookies");
        output.println("</title></head><body>");
        output.println("<h1>Welcome to cookies! (method doPost())</h1>");
        output.println(game + " is a great game.... maybe?");
        output.println("<br>sent cookie " + cookie.toString());
        output.println("<hr><a href=\"./SelectGame.html\">Scelta giochi</a>");
        output.println("<hr><a href=\"./GameRecommendation.html\">Giochi raccomandati</a>");
        output.println("</body></html>");
        output.close();
    }

    public void doGet(HttpServletRequest request,
                        HttpServletResponse response) 
        throws ServletException, IOException
    {
        PrintWriter output;
        Cookie cookies[];

        cookies = request.getCookies();

        response.setContentType("text/html");
        output = response.getWriter();

        output.println("<html><head>");
        output.println("<title>cookies II </title>");
        output.println("</head><body>");
        output.println("<h1>Recommendations (method doGet())</h1>");

        if(cookies != null) {
            for(int i=0; i<cookies.length; i++) 
                output.println(
                    cookies[i].getName() + " LINK: " + cookies[i].getValue() + "<br>"
                );
        }
        else {
            output.println("<h2>No Recommendations</h2>");
            output.println("You did not select a game or");
            output.println("the cookies have expired after " + maxAge + " seconds.");
        }

        output.println("<hr><a href=\"./SelectGame.html\">Scelta giochi</a>");
        output.println("<hr><a href=\"./GameRecommendation.html\">Giochi raccomandati</a>");
        output.println("</body></html>");
        output.close();
    }

}
