#include "ColliderFloor.h"

ColliderFloor::ColliderFloor(Mesh* mesh)
{
	this->mesh = mesh;
}

// Reference
// https://www.scenebeta.com/node/17755

bool ColliderFloor::isPointInTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 pos) {

	float orientation, abt, bct, cat;

	//calculamos la orientación del triangulo
	orientation = (v1.x - v3.x) * (v2.z - v3.z) - (v1.z - v3.z) * (v2.x - v3.x);

	//ahora calcularemos la orientación de los triángulos que tengan como uno de los vértices el 
	//punto del personaje, los triangulos serían ABT, BCT y CAT donde T es el punto del personaje
	abt = (v1.x - pos.x) * (v2.z - pos.z) - (v1.z - pos.z) * (v2.x - pos.x);
	bct = (v2.x - pos.x) * (v3.z - pos.z) - (v2.z - pos.z) * (v3.x - pos.x);
	cat = (v3.x - pos.x) * (v1.z - pos.z) - (v3.z - pos.z) * (v1.x - pos.x);

	//si la orientación del triángulo y la de los demás triángulos es igual a cero o mayor, el punto está dentro del triángulo
	if (orientation >= 0 && abt >= 0 && bct >= 0 && cat >= 0) {
		return 1;
	}

	//si la orientación del triángulo y la de los demás triángulos es menor que cero, el punto también está dentro del triángulo
	if (orientation < 0 && abt < 0 && bct < 0 && cat < 0) {
		return 1;
	}

	//si no se cumple ninguna de los requerimientos anteriores, el punto está fuera del triángulo
	return 0;
}

float ColliderFloor::heightOfTriangleAtPos(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 pos) {

	float A, B, C, D, height;

	//A, B y C son la normal del plano del triangulo
	A = v1.y * (v2.z - v3.z) + v2.y * (v3.z - v1.z) + v3.y * (v1.z - v2.z);
	B = v1.z * (v2.x - v3.x) + v2.z * (v3.x - v1.x) + v3.z * (v1.x - v2.x);
	C = v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y);
	D = -(v1.x * (v2.y * v3.z - v3.y * v2.z) + v2.x * (v3.y * v1.z - v1.y * v3.z) + v3.x * (v1.y * v2.z - v2.y * v1.z));

	//Ahora ponemos el valor de B a un número cercano a cero si su valor original es cero para que no de errores a la hora de hacer la división
	if (B == 0)
	{
		B = 0.01;
	}

	//calculamos la altura del punto
	height = -(D + A * pos.x + C * pos.z) / B;

	//devolvemos la altura del punto
	return height;
}


float ColliderFloor::getHeightAtPos(glm::vec3 pos) {

	float height = 0;// , tempHeight = 99999999, x1, y1, z1;

	int v1 = 0, v2 = 0, v3 = 0;

	//Una cosa buena de este código es que puedes escalar el modelo(no el que se va a dibujar sino el que se va a procesar)
	//x1 = pos.x / escala;
	//y1 = pos.y / escala;
	//z1 = pos.z / escala;

	//Mirar si el punto está dentro de la bounding box del modelo (si no lo está devuelve 0)
	//maxx, maxy y maxz son los puntos máximos y minx, miny y minz son los mínimos
	//if (pos.x > mod.maxx || pos.x < mod.minx || pos.y > mod.maxy || pos.y < mod.miny || pos.z > mod.maxz || pos.z < mod.minz)
	//{
	//	return 0;
	//}

	//Buscar el triangulo en el que las coordenada x y z están localizadas.
	for (int vertex = 1; vertex < mesh->getVertices().size(); vertex += 3) {
		//indices de la cara (vertices)
		//a = mesh->getVertices()[vertex].cara[0]; //número del primer vértice del triangulo
		//b = mesh->getVertices()[vertex].cara[3]; //número del segundo vértice del triangulo
		//c = mesh->getVertices()[vertex].cara[6]; //número del tercer vértice del triangulo

		v1 = vertex;
		v2 = vertex + 1;
		v3 = vertex + 2;

		//Mirar si el punto (solo se tienen en cuenta las coordenadas  x, z) está dentro de este triangulo (si no, pasar al siguiente)
		if (isPointInTriangle(mesh->getVertices()[v1], mesh->getVertices()[v2], mesh->getVertices()[v3], pos))
		{

			//conseguimos la altura de la intersección
			//asignamos la altura actual a una variable para luego compararla con la anterior
			height = heightOfTriangleAtPos(mesh->getVertices()[v1], mesh->getVertices()[v2], mesh->getVertices()[v3], pos);
			//esto sirve para conseguir la altura más cercana al personaje
			//if (abs(pos.y - height) > abs(pos.y - tempHeight))
			//{
			//	height = tempHeight; //si la altura anterior es más lejana a la altura temporal, actualizamos el valor de la altura
			//}
			break;
		}
	}

	//if (height == 99999999) {
	//	height = 0;
	//}

	return height;// *escala; //devuelve la altura conseguida
}