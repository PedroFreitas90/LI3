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
 * Classe que implementa o parsing do ficheiro Tags.xml
 *
 * @author Grupo 51
 */
public class TagHandler extends DefaultHandler {

    private TagBD tags = null;
    private Tag tag = null;

    /**
     * Devolve a base de dados de tags
     * @return TagBD
     */
    public TagBD getTags(){
        return tags;
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {

        if (qName.equalsIgnoreCase("row")) {

            tag = new Tag();

            String id = attributes.getValue("Id");
            tag.setTagId(Integer.parseInt(id));
            String name = attributes.getValue("TagName");
            tag.setTagName(name);
            

            if (tags == null)
                tags = new TagBD();
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException {
        if (qName.equalsIgnoreCase("row")) {
             tags.addTag(tag);
        }
    }

}
