#include "ColliderFloor.h"

ColliderFloor::ColliderFloor(std::set<Mesh*> meshes)
{
	this->meshes = meshes;
}

// Reference
// https://www.scenebeta.com/node/17755

bool ColliderFloor::isPointInTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 pos) {

	float orientation, abt, bct, cat;

	//calculamos la orientaci�n del triangulo
	orientation = (v1.x - v3.x) * (v2.z - v3.z) - (v1.z - v3.z) * (v2.x - v3.x);

	//ahora calcularemos la orientaci�n de los tri�ngulos que tengan como uno de los v�rtices el 
	//punto del personaje, los triangulos ser�an ABT, BCT y CAT donde T es el punto del personaje
	abt = (v1.x - pos.x) * (v2.z - pos.z) - (v1.z - pos.z) * (v2.x - pos.x);
	bct = (v2.x - pos.x) * (v3.z - pos.z) - (v2.z - pos.z) * (v3.x - pos.x);
	cat = (v3.x - pos.x) * (v1.z - pos.z) - (v3.z - pos.z) * (v1.x - pos.x);

	//si la orientaci�n del tri�ngulo y la de los dem�s tri�ngulos es igual a cero o mayor, el punto est� dentro del tri�ngulo
	if (orientation >= 0 && abt >= 0 && bct >= 0 && cat >= 0) {
		return 1;
	}

	//si la orientaci�n del tri�ngulo y la de los dem�s tri�ngulos es menor que cero, el punto tambi�n est� dentro del tri�ngulo
	if (orientation < 0 && abt < 0 && bct < 0 && cat < 0) {
		return 1;
	}

	//si no se cumple ninguna de los requerimientos anteriores, el punto est� fuera del tri�ngulo
	return 0;
}

float ColliderFloor::heightOfTriangleAtPos(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 pos) {

	float A, B, C, D, height;

	//A, B y C son la normal del plano del triangulo
	A = v1.y * (v2.z - v3.z) + v2.y * (v3.z - v1.z) + v3.y * (v1.z - v2.z);
	B = v1.z * (v2.x - v3.x) + v2.z * (v3.x - v1.x) + v3.z * (v1.x - v2.x);
	C = v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y);
	D = -(v1.x * (v2.y * v3.z - v3.y * v2.z) + v2.x * (v3.y * v1.z - v1.y * v3.z) + v3.x * (v1.y * v2.z - v2.y * v1.z));

	//Ahora ponemos el valor de B a un n�mero cercano a cero si su valor original es cero para que no de errores a la hora de hacer la divisi�n
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

	//Una cosa buena de este c�digo es que puedes escalar el modelo(no el que se va a dibujar sino el que se va a procesar)
	//x1 = pos.x / escala;
	//y1 = pos.y / escala;
	//z1 = pos.z / escala;

	//Mirar si el punto est� dentro de la bounding box del modelo (si no lo est� devuelve 0)
	//maxx, maxy y maxz son los puntos m�ximos y minx, miny y minz son los m�nimos
	//if (pos.x > mod.maxx || pos.x < mod.minx || pos.y > mod.maxy || pos.y < mod.miny || pos.z > mod.maxz || pos.z < mod.minz)
	//{
	//	return 0;
	//}

	//Buscar el triangulo en el que las coordenada x y z est�n localizadas.
	
    for(Mesh* mesh : meshes) {
		for (int vertex = 1; vertex < mesh->getVertices().size(); vertex += 3) {
			//indices de la cara (vertices)
			//a = mesh->getVertices()[vertex].cara[0]; //n�mero del primer v�rtice del triangulo
			//b = mesh->getVertices()[vertex].cara[3]; //n�mero del segundo v�rtice del triangulo
			//c = mesh->getVertices()[vertex].cara[6]; //n�mero del tercer v�rtice del triangulo

			v1 = vertex;
			v2 = vertex + 1;
			v3 = vertex + 2;

			//Mirar si el punto (solo se tienen en cuenta las coordenadas  x, z) est� dentro de este triangulo (si no, pasar al siguiente)
			if (isPointInTriangle(mesh->getVertices()[v1], mesh->getVertices()[v2], mesh->getVertices()[v3], pos))
			{

				//conseguimos la altura de la intersecci�n
				//asignamos la altura actual a una variable para luego compararla con la anterior
				height = heightOfTriangleAtPos(mesh->getVertices()[v1], mesh->getVertices()[v2], mesh->getVertices()[v3], pos);
				//esto sirve para conseguir la altura m�s cercana al personaje
				//if (abs(pos.y - height) > abs(pos.y - tempHeight))
				//{
				//	height = tempHeight; //si la altura anterior es m�s lejana a la altura temporal, actualizamos el valor de la altura
				//}
				break;
			}
		}
	}

	//if (height == 99999999) {
	//	height = 0;
	//}

	return height;// *escala; //devuelve la altura conseguida
}