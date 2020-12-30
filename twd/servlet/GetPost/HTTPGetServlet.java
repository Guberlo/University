import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class HTTPGetServlet extends HttpServlet {
    public void doGet( HttpServletRequest request,
                        HttpServletResponse response)
        throws ServletException, IOException
    {
        PrintWriter output;

        response.setContentType("text/html");
        output = response.getWriter();

        // Create and send HTML page to client
        StringBuffer buf = new StringBuffer();
        buf.append("<html><head><title>\n");
        buf.append("A Simple Servlet Example\n");
        buf.append("</title></head><body>\n");
        buf.append("<h1>Welcome to Servlets!</h1>\n");
        buf.append("<h1>CE LA FECIII!</h1>\n");
        buf.append("</body></html>\n");
        output.println(buf.toString());
        output.close();
    }
}