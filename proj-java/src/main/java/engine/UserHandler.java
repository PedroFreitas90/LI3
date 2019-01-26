package engine;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;

import javax.xml.namespace.QName;
import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
import java.time.LocalDate;
import java.util.TreeSet;
import java.util.Set;

/**
 * Classe que efetua o parsing do ficheiro Users.xml
 *
 * @author Grupo 51
 */
public class UserHandler extends DefaultHandler {

    private UserBD users = null;
    private User usr = null;

    /**
     * Devolve a base de dados de users
     * @return UserBD
     */
    public UserBD getUsers(){
        return users;
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {

        if (qName.equalsIgnoreCase("row")) {

            usr = new User();

            String id = attributes.getValue("Id");
            if(id != null)
                usr.setUserId(Integer.parseInt(id));
            String reputation = attributes.getValue("Reputation");
            if(reputation != null)
                usr.setUserRep(Integer.parseInt(reputation));
            String name = attributes.getValue("DisplayName");
            if(name != null)
                usr.setUserName(name);
            String aboutMe = attributes.getValue("AboutMe");
            if(aboutMe != null)
                usr.setUserBio(aboutMe);

            if (users == null)
                users = new UserBD();
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException {
        if (qName.equalsIgnoreCase("row")) {
             users.addUser(usr);
        }
    }

}
